// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverLog.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "LogSpawner.h"
#include "BeaverGameInstance.h"

ABeaverLog::ABeaverLog()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsJumped                     = false;
    logParams.speed               = 50.0f;
    logParams.lifeTime            = 20;
    logParams.impactCounterMax    = 3;
    scaleSpeed                    = 1.f;
    boxComponent               = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsule Component"));

    SetRootComponent(boxComponent);
    boxComponent->GetCollisionResponseToChannel(ECC_GameTraceChannel1);
    this->Tags.Add("Log");
}

void ABeaverLog::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(logParams.lifeTime);
}

void ABeaverLog::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
 
    LogMove(DeltaTime);
}

void ABeaverLog::LogMove(float DeltaTime)
{

    float deltaSpeed = DeltaTime * logParams.speed*scaleSpeed;

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
        GetWorldTimerManager().SetTimer(timerHandle, this, &ABeaverLog::BeaverLogScore, 2);
    }
}
void ABeaverLog::BeaverLogScore()
{
    Cast<ABeaverGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddScore(1);
    Cast<ABeaverGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddLifeTime(2);
    Destroy();
}

void ABeaverLog::BeaverLogSlivers()
{
    Cast<UBeaverGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->AddSlivers(1); 
}
