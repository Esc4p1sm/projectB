// Copyright (c) 2024 Allure Games.

#include "Hourglass.h"
#include "Components/SphereComponent.h"
#include "LogSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "PlayerBeaver.h"
#include "BeaverShield.h"
#include "BeaverGameMode.h"

AHourglass::AHourglass()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    StaticMesh      = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hourglass"));

    SetRootComponent(SphereComponent);

    StaticMesh->SetupAttachment(RootComponent);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AHourglass::BeginPlay()
{
    Super::BeginPlay();

    SphereComponent->SetGenerateOverlapEvents(true);
    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHourglass::OnOverlapBegin);

    SetLifeSpan(HourParams.LifeTime);
}

void AHourglass::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHourglass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    PlayerBeaver = Cast<APlayerBeaver>(OtherActor);

    if (IsValid(PlayerBeaver) && OtherActor->IsA(APlayerBeaver::StaticClass()))
    {
        SlowdownLogs();

        SetActorHiddenInGame(true);

        SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AHourglass::SlowdownLogs()
{
    FTimerHandle timerHandle;

    ABeaverLog::CustomSpeedScale = HourParams.SlowdownScale;

    GetWorldTimerManager().ClearTimer(AHourglass::TimerHandle_LifeSpanExpired);

    GetWorldTimerManager().SetTimer(timerHandle, this, &AHourglass::ReturnToDefault, HourParams.timeForSlow, false);
}

void AHourglass::ReturnToDefault()
{
    HourParams.SlowdownScale = 1;

    ABeaverLog::CustomSpeedScale = HourParams.SlowdownScale;

    Destroy();
}
