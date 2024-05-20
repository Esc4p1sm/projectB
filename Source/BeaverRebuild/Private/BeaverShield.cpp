// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverShield.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerBeaver.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverLog.h"
#include "Libs/BeaverTypes.h"

ABeaverShield::ABeaverShield()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Shield"));
    StaticMesh      = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Shield"));

    SetRootComponent(SphereComponent);
}

void ABeaverShield::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(LifeTime);

    SphereComponent->OnComponentHit.AddDynamic(this, &ABeaverShield::OnOverlapShieldBegin);

    ChangeBeaverCapsuleCollision(ECollisionResponse::ECR_Ignore);

    ChangeShieldComponentsParams();
}

void ABeaverShield::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    ChangeBeaverCapsuleCollision(ECollisionResponse::ECR_Overlap);
}

void ABeaverShield::OnOverlapShieldBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                         FVector NormalImpulse, const FHitResult& Hit)
{
    ABeaverLog* beaverLog = Cast<ABeaverLog>(OtherActor);

    if (IsValid(beaverLog) && OtherActor->IsA(ABeaverLog::StaticClass()))
    {
        beaverLog->LogParams.ScaleSpeed   = Speedup;
        beaverLog->LogParams.LogDirection = Hit.ImpactNormal;

        FTimerHandle timerHandle;
        GetWorldTimerManager().SetTimer(timerHandle, this, &ABeaverShield::DestroyPickedShield, 0.5f, false);
    }
}

void ABeaverShield::DestroyPickedShield()
{
    ChangeBeaverCapsuleCollision(ECollisionResponse::ECR_Overlap);
    Destroy();
}

void ABeaverShield::ChangeShieldComponentsParams()
{
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->AttachToComponent(PlayerBeaver->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    SphereComponent->SetUseCCD(true);

    StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    StaticMesh->AttachToComponent(PlayerBeaver->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ABeaverShield::ChangeBeaverCapsuleCollision(const ECollisionResponse Response)
{
    PlayerBeaver = StaticCast<APlayerBeaver*>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerBeaver::StaticClass()));

    if (IsValid(PlayerBeaver))
    {
        PlayerBeaver->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_LOGS_OBJECT_CHANNEL, Response);
    }
}
