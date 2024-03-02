// Fill out your copyright notice in the Description page of Project Settings.

#include "Hourglass.h"
#include "Components/SphereComponent.h"
#include "LogSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "PlayerBeaver.h"
#include "BeaverShield.h"
AHourglass::AHourglass()
{
    PrimaryActorTick.bCanEverTick = false;
    bItemPicked                   = true;
    ptrBeaver                     = nullptr;
    hourParams.slowdownScale      = 2.f;
    hourParams.timeForSlow        = 9;
    hourParams.lifeTime           = 15;
    sphereComponent               = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    staticMesh                    = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hourglass"));

    SetRootComponent(sphereComponent);
    staticMesh->SetupAttachment(RootComponent);
    sphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AHourglass::BeginPlay()
{
    Super::BeginPlay();

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

    if (IsValid(ptrBeaver))
    {
        SlowdownLogs();
        SetActorHiddenInGame(true);
        sphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AHourglass::SlowdownLogs()
{
    SetLifeSpan(hourParams.lifeTime / 2);

    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), (1 / hourParams.slowdownScale));

    ptrBeaver->CustomTimeDilation = (1 * hourParams.slowdownScale);

    if (bItemPicked) ReturnToDefault();
}

void AHourglass::ReturnToDefault()
{
    bItemPicked              = false;
    hourParams.slowdownScale = 1;

    FTimerHandle timerHandle;
    GetWorldTimerManager().SetTimer(timerHandle, this, &AHourglass::SlowdownLogs, hourParams.timeForSlow / 2, false);
}
