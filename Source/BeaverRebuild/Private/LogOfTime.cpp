// Fill out your copyright notice in the Description page of Project Settings.

#include "LogOfTime.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Hourglass.h"

ALogOfTime::ALogOfTime()
{
    LogParams.TypeOfLog = ELogType::ClockedLog;
}

void ALogOfTime::SpawnHourglass()
{
    GetWorld()->SpawnActor<AHourglass>(Hourglass, GetActorLocation(), FRotator::ZeroRotator);
}

void ALogOfTime::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (bIsJumped) SpawnHourglass(); 
}
