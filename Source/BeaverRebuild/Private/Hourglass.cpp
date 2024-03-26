// Fill out your copyright notice in the Description page of Project Settings.

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
    bItemPicked                   = true;
    ptrBeaver                     = nullptr;
    hourParams.slowdownScale      = 0.5f;
    hourParams.timeForSlow        = 9;
    hourParams.lifeTime           = 15;

    sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    staticMesh      = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hourglass"));

    SetRootComponent(sphereComponent);
    staticMesh->SetupAttachment(RootComponent);
    sphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AHourglass::BeginPlay()
{
    Super::BeginPlay();

    check(staticMesh);

    sphereComponent->SetGenerateOverlapEvents(true);
    sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHourglass::OnOverlapBegin);

    SetLifeSpan(hourParams.lifeTime);
}

void AHourglass::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHourglass::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    ptrBeaver = Cast<APlayerBeaver>(OtherActor);

    if (IsValid(ptrBeaver) && OtherActor->IsA(APlayerBeaver::StaticClass()))
    {
        SlowdownLogs();

        SetActorHiddenInGame(true);

        sphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AHourglass::SlowdownLogs()
{
    FTimerHandle timerHandle;

    ABeaverLog::customSpeedScale = hourParams.slowdownScale;

    GetWorldTimerManager().ClearTimer(AHourglass::TimerHandle_LifeSpanExpired);

    GetWorldTimerManager().SetTimer(timerHandle, this, &AHourglass::ReturnToDefault, hourParams.timeForSlow, false);
}

void AHourglass::ReturnToDefault()
{
    hourParams.slowdownScale = 1;

    ABeaverLog::customSpeedScale = hourParams.slowdownScale;

    Destroy();
}
