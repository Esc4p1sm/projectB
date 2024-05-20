// Fill out your copyright notice in the Description page of Project Settings.

#include "HugeBeaverLog.h"
#include "BeaverLog.h"
#include "Kismet/GameplayStatics.h"
#include "LogSpawner.h"
#include "Libs/BeaverBPFunctionLib.h"

AHugeBeaverLog::AHugeBeaverLog()
{
    LogParams.TypeOfLog = ELogType::HugeLog;
}

void AHugeBeaverLog::SpawnLogs()
{
    const FVector actorLocation = GetActorLocation();

    for (int32 i = 0; i < 3; ++i)
    {
        const FVector Location = {actorLocation.X, actorLocation.Y + RangeBtwnLogs, actorLocation.Z};
        const auto Logs        = GetWorld()->SpawnActor<ABeaverLog>(StdLogs, Location, FRotator ::ZeroRotator);

        if (Logs)
        {
            Logs->LogParams.LogDirection     = UBeaverBPFunctionLib::MakeRandomDirection(45, 75);
            Logs->LogParams.Speed            = this->LogParams.Speed;
            Logs->LogParams.ImpactCounterMax = 5;
        }
        RangeBtwnLogs -= 100;
    }
}

void AHugeBeaverLog::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (bIsJumped)
    {
        SpawnLogs();
    }

    Super::EndPlay(EndPlayReason);
}