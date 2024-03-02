// Fill out your copyright notice in the Description page of Project Settings.

#include "LogSpawner.h"
#include "BeaverLog.h"
#include "BeaverGameMode.h"
#include "PlayerBeaver.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libs/BeaverBPFunctionLib.h"

// Sets default values
ALogSpawner::ALogSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    spawnLogParams.initialSpeed   = 50.f;
    spawnLogParams.minAngle       = 45.f;
    spawnLogParams.maxAngle       = 75.f;
    spawnLogParams.speedChange    = 1.f;
    spawnParams.spawnRangeLeft    = -170;
    spawnParams.spawnRangeRight   = 150;
    spawnParams.distBetweenLogs   = 100;
    spawnParams.spawnRate         = 3.f;
    spawnParams.stdChance         = 0.9f;
    spawnParams.rateChange        = 0.03f;
    spawnParams.spawnerLocation   = FVector{50.f, 20.f, 510.f};
}

void ALogSpawner::BeginPlay()
{
    Super::BeginPlay();

    Cast<ABeaverGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->logSpawner = this;

    StartSpawn();

    SetActorLocation(spawnParams.spawnerLocation);
}

void ALogSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALogSpawner::SpawnLog()
{
    const FVector direction =
        UBeaverBPFunctionLib::MakeRandomDirection(spawnLogParams.minAngle, spawnLogParams.maxAngle);

    SetRandomLocation();

    if (IsValid(RandomizerOfLogs()))
    {
        auto newLog = GetWorld()->SpawnActor<ABeaverLog>(RandomizerOfLogs(), spawnParams.spawnerLocation, FRotator::ZeroRotator);

        if (IsValid(newLog))
        {
            newLog->logParams.speed        = spawnLogParams.initialSpeed;
            newLog->logParams.logDirection = direction;
        }
        // newLog->CustomTimeDilation  = slowdownScale;
    }

    ChangeParamsOverTime();
}

void ALogSpawner::ChangeParamsOverTime()
{
    spawnParams.spawnRate -= spawnParams.rateChange;
    spawnLogParams.initialSpeed += spawnLogParams.speedChange;
    spawnParams.spawnRate       = FMath::Clamp(spawnParams.spawnRate, 0.5f, 20);
    spawnLogParams.initialSpeed = FMath::Clamp(spawnLogParams.initialSpeed, 1, 180);

    GetWorldTimerManager().SetTimer(timerHandle, this, &ALogSpawner::SpawnLog, spawnParams.spawnRate, false);
}

TSubclassOf<ABeaverLog> ALogSpawner::RandomizerOfLogs()
{
    int32 randIterator;

    UKismetMathLibrary::RandomBoolWithWeight(spawnParams.stdChance)
        ? randIterator = 0
        : randIterator = FMath::RandRange(1, listOfLogs.Num() - 1);

    auto logForSpawn = listOfLogs[randIterator];

    return logForSpawn;
}

// FVector ALogSpawner::MakeRandomDirection()
//{
//     FVector direction(0.f, 0.f, -1.f);
//     float randAngle = FMath::RandRange(spawnLogParams.minAngle, spawnLogParams.maxAngle);
//     direction       = direction.RotateAngleAxis(randAngle, FVector(1.f, 0.f, 0.f));
//
//     if (FMath::RandBool())
//     {
//         direction.Y *= -1;
//     }
//
//     return direction;
// }

void ALogSpawner::SetRandomLocation()
{
    while (true)
    {
        float y     = FMath::RandRange(spawnParams.spawnRangeLeft, spawnParams.spawnRangeRight);
        bool bRange = fabs(spawnParams.spawnerLocation.Y - y) >= spawnParams.distBetweenLogs;

        if (bRange)
        {
            spawnParams.spawnerLocation.Y = y;
            break;
        }
    }
}

void ALogSpawner::DestroyAllLogs()
{
    for (FActorIterator logIter(GetWorld()); logIter; ++logIter)
    {
        ABeaverLog *log = Cast<ABeaverLog>(*logIter);
        if (IsValid(log))
        {
            log->Destroy();
        }
    }
}

void ALogSpawner::StopSpawn()
{
    DestroyAllLogs();
    GetWorldTimerManager().ClearTimer(timerHandle);
}

void ALogSpawner::StartSpawn()
{
    GetWorldTimerManager().SetTimer(timerHandle, this, &ALogSpawner::SpawnLog, spawnParams.spawnRate, false, 0.1f);
}
