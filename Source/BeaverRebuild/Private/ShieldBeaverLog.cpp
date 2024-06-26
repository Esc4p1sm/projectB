// Copyright (c) 2024 Allure Games.

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

    LogParams.TypeOfLog = ELogType ::TarLog;

    PlayerBeaver = StaticCast<APlayerBeaver*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AShieldBeaverLog::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (bIsJumped)
    {
        GetWorld()->SpawnActor<ABeaverShield>(Shield);
    }
}
