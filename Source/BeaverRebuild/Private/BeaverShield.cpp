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
    lifeTime                      = 10;
    speedup                       = 10.f;

    sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Shield"));
    staticMesh      = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Shield"));

    SetRootComponent(sphereComponent);
    ptrBeaver = nullptr;
}

void ABeaverShield::BeginPlay()
{
    Super::BeginPlay();

    check(staticMesh);

    SetLifeSpan(lifeTime);

    sphereComponent->OnComponentHit.AddDynamic(this, &ABeaverShield::OnOverlapShieldBegin);

    ChangeBeaverCapsuleCollision(ECollisionResponse::ECR_Ignore);

    ChangeShieldComponentsParams();
}

void ABeaverShield::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    ChangeBeaverCapsuleCollision(ECollisionResponse::ECR_Overlap);
}

void ABeaverShield::OnOverlapShieldBegin(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                         FVector NormalImpulse, const FHitResult &Hit)
{
    ABeaverLog *beaverLog = Cast<ABeaverLog>(OtherActor);
    
    if (IsValid(beaverLog) && OtherActor->IsA(ABeaverLog::StaticClass()))
    {
        beaverLog->logParams.scaleSpeed   = speedup;
        beaverLog->logParams.logDirection = Hit.ImpactNormal;

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
    sphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    sphereComponent->AttachToComponent(ptrBeaver->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    sphereComponent->SetUseCCD(true);

    staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    staticMesh->AttachToComponent(ptrBeaver->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ABeaverShield::ChangeBeaverCapsuleCollision(const ECollisionResponse response)
{
    ptrBeaver = StaticCast<APlayerBeaver*>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerBeaver::StaticClass()));

    if (IsValid(ptrBeaver))
    {
        ptrBeaver->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_LogsObjectChannel, response);
    }
}
