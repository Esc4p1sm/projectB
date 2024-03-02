// Fill out your copyright notice in the Description page of Project Settings.

#include "HugeBeaverLog.h"
#include "BeaverLog.h"
#include "Kismet/GameplayStatics.h"
#include "LogSpawner.h"
#include "Libs/BeaverBPFunctionLib.h"


AHugeBeaverLog::AHugeBeaverLog()
{
    rangeBtwnLogs = 100;
}

void AHugeBeaverLog::SpawnLogs()
{
    const FVector actorLocation = GetActorLocation();

    for (int32 i = 0; i < 3; ++i)
    {
        const FVector loc = {actorLocation.X, actorLocation.Y + rangeBtwnLogs, actorLocation.Z};
        auto *logs        = GetWorld()->SpawnActor<ABeaverLog>(stdLogs, loc, FRotator ::ZeroRotator);

        if (logs)
        {
            logs->logParams.logDirection     = UBeaverBPFunctionLib::MakeRandomDirection(45, 75);
            logs->logParams.speed            = this->logParams.speed;
            logs->logParams.impactCounterMax = 5;
        }
        rangeBtwnLogs -= 100;
    }
}

void AHugeBeaverLog::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (bIsJumped) SpawnLogs();

    Super::EndPlay(EndPlayReason);
}