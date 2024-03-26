// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBeaverLog.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerBeaver.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "BeaverShield.h"

void AShieldBeaverLog::BeginPlay()
{
    Super::BeginPlay();

    ptrBeaver = StaticCast<APlayerBeaver*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AShieldBeaverLog::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (bIsJumped) GetWorld()->SpawnActor<ABeaverShield>(shield);     
}


