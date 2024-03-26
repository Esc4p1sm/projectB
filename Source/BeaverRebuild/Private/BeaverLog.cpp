// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverLog.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "LogSpawner.h"
#include "BeaverGameInstance.h"
#include "Libs/BeaverTypes.h"

float ABeaverLog::customSpeedScale = 1.f;

ABeaverLog::ABeaverLog()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsJumped                     = false;
    logParams.speed               = 50.0f;
    logParams.scaleSpeed          = 1.f;
    logParams.lifeTime            = 20;
    logParams.impactCounterMax    = 3;
    logParams.additionalSlivers   = 1;
    logParams.additionalTime      = 2;
    logParams.additionalScore     = 1;
    logParams.timeToDestruction   = 2;

    boxComponent               = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsule Component"));

    SetRootComponent(boxComponent);
    boxComponent->GetCollisionResponseToChannel(ECC_MarkLogsTraceChannel);
    this->Tags.Add("Log");
}

void ABeaverLog::BeginPlay()
{
    Super::BeginPlay();

    boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABeaverLog::OnOverlapBegin);
    SetLifeSpan(logParams.lifeTime);
}

void ABeaverLog::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
 
    LogMove(DeltaTime);
}

void ABeaverLog::LogMove(float DeltaTime)
{

    float deltaSpeed = DeltaTime * logParams.speed * logParams.scaleSpeed*customSpeedScale;

    AddActorWorldOffset(logParams.logDirection * deltaSpeed, true, &hitResult);

    if (hitResult.bBlockingHit)
    {
        logParams.impactCounterMax--;

        if (logParams.impactCounterMax == 0)
        {
            Destroy();
        }

        reflectionVector       = FMath::GetReflectionVector(logParams.logDirection, hitResult.ImpactNormal);
        logParams.logDirection = FVector{0, reflectionVector.Y, reflectionVector.Z};
        logParams.logDirection.Normalize();
    }
}

void ABeaverLog::MarkAsJumped()
{
    if (!bIsJumped)
    {
        bIsJumped = true;
        BeaverLogSlivers();
        GetWorldTimerManager().SetTimer(timerHandle, this, &ABeaverLog::BeaverLogScore, logParams.timeToDestruction);
    }
}
void ABeaverLog::BeaverLogScore()
{
    StaticCast<ABeaverGameMode*>(UGameplayStatics::GetGameMode(GetWorld()))->AddScore(logParams.additionalScore);
    StaticCast<ABeaverGameMode*>(UGameplayStatics::GetGameMode(GetWorld()))->AddLifeTime(logParams.additionalTime);
    Destroy();
}

void ABeaverLog::BeaverLogSlivers()
{
    StaticCast<UBeaverGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()))->AddSlivers(logParams.additionalSlivers);
}

void ABeaverLog::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                   int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor->IsA(APlayerBeaver::StaticClass()) && IsValid(GetWorld()->GetAuthGameMode()))
    {
        onFinishRound.Broadcast();
        OtherActor->Destroy();
    }
}