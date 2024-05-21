// Copyright (c) 2024 Allure Games.

#include "LogSpawner.h"
#include "BeaverLog.h"
#include "BeaverGameMode.h"
#include "PlayerBeaver.h"
#include "BeaverGameInstance.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libs/BeaverBPFunctionLib.h"

ALogSpawner::ALogSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALogSpawner::BeginPlay()
{
    Super::BeginPlay();

    StaticCast<ABeaverGameMode*>(UGameplayStatics::GetGameMode(GetWorld()))->LogSpawner = this;

    // StartSpawn();

    SetActorLocation(SpawnParams.SpawnerLocation);
}

void ALogSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALogSpawner::SpawnLog()
{
    if (!GetWorld()->GetAuthGameMode())
    {
        return;
    }

    const FVector Direction = UBeaverBPFunctionLib::MakeRandomDirection(SpawnLogParams.MinAngle, SpawnLogParams.MaxAngle);
    const auto LogForSpawn  = ListOfLogs[GetRandIndex()];

    SetRandomLocation();

    if (IsValid(LogForSpawn))
    {
        auto NewLog = GetWorld()->SpawnActor<ABeaverLog>(LogForSpawn, SpawnParams.SpawnerLocation, FRotator{0.f, 90.f, 90.f});

        NewLog->LogParams.Speed        = SpawnLogParams.InitialSpeed;
        NewLog->LogParams.LogDirection = Direction;
        NewLog->OnFinishRound.AddDynamic(Cast<ABeaverGameMode>(GetWorld()->GetAuthGameMode()), &ABeaverGameMode::FinishRound);

        Cast<UBeaverGameInstance>(GetWorld()->GetGameInstance())->linkLog(NewLog);
    }

    ChangeParamsOverTime();
}

void ALogSpawner::ChangeParamsOverTime()
{
    SpawnParams.SpawnRate -= SpawnParams.RateChange;
    SpawnLogParams.InitialSpeed += SpawnLogParams.SpeedChange;

    SpawnParams.SpawnRate       = FMath::Clamp(SpawnParams.SpawnRate, 0.5f, 20);
    SpawnLogParams.InitialSpeed = FMath::Clamp(SpawnLogParams.InitialSpeed, 1, 180);

    GetWorldTimerManager().SetTimer(TimerHandle, this, &ALogSpawner::SpawnLog, SpawnParams.SpawnRate, false);
}

int32 ALogSpawner::GetRandIndex()
{
    int32 RandIterator;

    UKismetMathLibrary::RandomBoolWithWeight(SpawnParams.StdChance) ? RandIterator = 0
                                                                    : RandIterator = FMath::RandRange(1, ListOfLogs.Num() - 1);

    return RandIterator;
}

void ALogSpawner::SetRandomLocation()
{
    while (true)
    {
        float NewLocationY = FMath::RandRange(SpawnParams.SpawnRangeLeft, SpawnParams.SpawnRangeRight);
        bool bIsRange      = fabs(SpawnParams.SpawnerLocation.Y - NewLocationY) >= SpawnParams.DistBetweenLogs;

        if (bIsRange)
        {
            SpawnParams.SpawnerLocation.Y = NewLocationY;

            break;
        }
    }
}

void ALogSpawner::DestroyAllLogs()
{
    for (FActorIterator LogIter(GetWorld()); LogIter; ++LogIter)
    {
        ABeaverLog* Log = Cast<ABeaverLog>(*LogIter);

        if (IsValid(Log))
        {
            Log->Destroy();
        }
    }
}

void ALogSpawner::StopSpawn()
{
    DestroyAllLogs();
    GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ALogSpawner::StartSpawn()
{
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ALogSpawner::SpawnLog, SpawnParams.SpawnRate, false, 0.1f);
}
