// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverLogSwamp.h"
#include "BeaverGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ABeaverLogSwamp::ABeaverLogSwamp()
{
    swampAdditionalTime = 5.f;

    ABeaverLogSwamp::boxComponent->OnComponentHit.AddDynamic(this, &ABeaverLogSwamp::OnComponentHit);
}

void ABeaverLogSwamp::OnComponentHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                     FVector NormalImpulse, const FHitResult &Hit)
{
    if (IsValid(GetWorld()) && OtherActor->IsA(APlayerBeaver::StaticClass()))
    {
        StaticCast<ABeaverGameMode *>(UGameplayStatics::GetGameMode(GetWorld()))->AddLifeTime(swampAdditionalTime);
        Destroy();
    } 
}
