// Copyright (c) 2024 Allure Games.

#include "BeaverLog.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h"
#include "Components/CapsuleComponent.h"
#include "LogSpawner.h"
#include "BeaverGameInstance.h"
#include "Libs/BeaverTypes.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "GeometryCollection/GeometryCollection.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Sound/SoundCue.h"

float ABeaverLog::CustomSpeedScale = 1.f;

ABeaverLog::ABeaverLog()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsJumped                     = false;
    LogParams.TypeOfLog           = ELogType::StandardLog;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));

    SetRootComponent(CapsuleComponent);

    CapsuleComponent->GetCollisionResponseToChannel(ECC_MARK_LOGS_TRACE_CHANNEL);
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABeaverLog::OnOverlapBegin);

    this->Tags.Add("Log");
}

void ABeaverLog::PostInitProperties()
{
    Super::PostInitProperties();  
}

void ABeaverLog::BeginPlay()
{
    Super::BeginPlay();

    FillArrayByComponents();

    GetWorldTimerManager().SetTimer(TimerToDestroy, this, &ABeaverLog::DestroyLogByTime, LogParams.LifeTime, false);
}

void ABeaverLog::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    LogRotation(DeltaTime);

    LogMove(DeltaTime);
}

void ABeaverLog::LogMove(float DeltaTime)
{

    float DeltaSpeed = DeltaTime * LogParams.Speed * LogParams.ScaleSpeed * CustomSpeedScale;

    AddActorWorldOffset(LogParams.LogDirection * DeltaSpeed, true, &HitResult);

    if (HitResult.bBlockingHit)
    {
        if (ImpactSound)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
        }

        GraduallyDestroyBark();

        LogParams.ImpactCounterMax--;

        if (LogParams.ImpactCounterMax == 0)
        {
            DestroyCoreLog();
        }

        ReflectionVector       = FMath::GetReflectionVector(LogParams.LogDirection, HitResult.ImpactNormal);
        LogParams.LogDirection = FVector{0, ReflectionVector.Y, ReflectionVector.Z};
        LogParams.LogDirection.Normalize();
    }
}

void ABeaverLog::LogRotation(float DeltaTime)
{
    float AngularSpeedByLogDirection = LogParams.AngleRotation * LogParams.LogDirection.GetSafeNormal().Y * DeltaTime;
    FQuat NewLogLocalRotation        = FQuat{FRotator{0, AngularSpeedByLogDirection, 0}};

    AddActorLocalRotation(NewLogLocalRotation);
}

void ABeaverLog::MarkAsJumped()
{
    if (!bIsJumped)
    {
        bIsJumped = true;
        BeaverLogSlivers();
        GetWorldTimerManager().SetTimer(TimerHandle, this, &ABeaverLog::BeaverLogScore, LogParams.TimeToDestruction);
    }
}
void ABeaverLog::BeaverLogScore()
{
    const auto GameMode = StaticCast<ABeaverGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));

    GameMode->AddScore(LogParams.AdditionalScore);
    GameMode->AddLifeTime(LogParams.AdditionalTime);

    OnLogScored.Broadcast(LogParams.TypeOfLog);
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Log broadcasted")));
    Destroy();
}

void ABeaverLog::BeaverLogSlivers()
{
    StaticCast<UBeaverGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()))->AddSlivers(LogParams.AdditionalSlivers);
}

void ABeaverLog::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(APlayerBeaver::StaticClass()) && IsValid(GetWorld()->GetAuthGameMode()))
    {
        OnFinishRound.Broadcast();

        OtherActor->Destroy();
    }
}

void ABeaverLog::FillArrayByComponents()
{
   this->GetComponents<UStaticMeshComponent>(LogComponents);
}

void ABeaverLog::GraduallyDestroyBark()
{
    int32 RandIndex = FMath::RandRange(3, LogComponents.Num() - 1);

    if (LogComponents.IsEmpty())
    {
        return;
    }

    if (LogParams.ImpactCounterMax > 2)
    {
        bool IsComponentTagBark = (LogComponents[RandIndex]->ComponentTags[0] == FName("Bark")) && (LogComponents[RandIndex]);

        if (IsComponentTagBark)
        {
            LogComponents[RandIndex]->DetachFromComponent(FDetachmentTransformRules{EDetachmentRule::KeepWorld, false});
            LogComponents[RandIndex]->SetSimulatePhysics(true);

            LogComponents.RemoveAt(RandIndex);
        }
    }
    else
    {
        for (const auto& Element : LogComponents)
        {
            if (Element->ComponentTags[0] == FName("Bark"))
            {
                Element->DetachFromComponent(FDetachmentTransformRules{EDetachmentRule::KeepWorld, false});
                Element->SetSimulatePhysics(true);
            }
        }
    }
}

void ABeaverLog::DestroyCoreLog()
{
    if (LogComponents.IsEmpty())
    {
        return;
    }

    for (const auto& Element : LogComponents)
    {
        if (Element->ComponentTags[0] == FName("Core"))
        {
            Element->DetachFromComponent(FDetachmentTransformRules{EDetachmentRule::KeepWorld, false});
            Element->SetSimulatePhysics(true);
        }
    }

    this->SetLifeSpan(2.f);
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABeaverLog::DestroyLogByTime()
{
    this->Destroy();
}

void ABeaverLog::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}