// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverShield.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerBeaver.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverLog.h"


ABeaverShield::ABeaverShield()
{
    PrimaryActorTick.bCanEverTick = false;
    lifeTime                      = 10;
    speedup                       = 10.f;
    sphereComponent               = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Shield"));
    staticMesh                    = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Shield"));
    RootComponent                 = sphereComponent;
    ptrBeaver                     = nullptr;
}

void ABeaverShield::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(lifeTime);

    ptrBeaver = Cast<APlayerBeaver>(UGameplayStatics::GetActorOfClass(GetWorld(),APlayerBeaver::StaticClass()));
    
    sphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    sphereComponent->SetUseCCD(true);
    sphereComponent->AttachToComponent(ptrBeaver->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    sphereComponent->OnComponentHit.AddDynamic(this, &ABeaverShield::OnOverlapShieldBegin);

    staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    staticMesh->AttachToComponent(ptrBeaver->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

    ptrBeaver->GetCapsuleComponent()->SetGenerateOverlapEvents(false);
}

void ABeaverShield::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABeaverShield::OnOverlapShieldBegin(UPrimitiveComponent *HitComponent,
                                         AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse,
                                         const FHitResult &Hit)
{
    ABeaverLog *beaverLog = Cast<ABeaverLog>(OtherActor);

    if (IsValid(beaverLog))
    {
        beaverLog->scaleSpeed = speedup;
        beaverLog->logParams.logDirection = Hit.ImpactNormal;

        FTimerHandle timerHandle;
        GetWorldTimerManager().SetTimer(timerHandle, this, &ABeaverShield::DestroyPickedShield, 0.5f,
                                        false);
    }
}

void ABeaverShield::DestroyPickedShield()
{
    ptrBeaver->GetCapsuleComponent()->SetGenerateOverlapEvents(true);
    Destroy();
}


