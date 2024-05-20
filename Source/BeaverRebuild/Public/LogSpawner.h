// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BeaverLog.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "Interfaces/HourglassInteract.h"
#include "LogSpawner.generated.h"

USTRUCT(BlueprintType)
struct FSpawnerParameters : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnerLocation = FVector{50.f, 20.f, 510.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnRate = 3.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StdChance = 0.9f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RateChange = 0.03f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SpawnRangeLeft = -170;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SpawnRangeRight = 150;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DistBetweenLogs = 100;
};

USTRUCT(BlueprintType)
struct FSpawningLogParameters : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinAngle = 45.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxAngle = 75.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialSpeed = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpeedChange = 1.f;
};

UCLASS()
class BEAVERREBUILD_API ALogSpawner : public AActor /*, public IHourglassInteract*/
{
    GENERATED_BODY()

  public:
    ALogSpawner();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

  public:
    /* Public variables */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objects for spawn");
    TArray<TSubclassOf<class ABeaverLog>> ListOfLogs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner parameters")
    FSpawnerParameters SpawnParams;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning log parameters")
    FSpawningLogParameters SpawnLogParams;

    /* Public functions */
    UFUNCTION(BlueprintCallable)
    void StopSpawn();

    UFUNCTION(BlueprintCallable)
    void StartSpawn();

    UFUNCTION(BlueprintCallable)
    void DestroyAllLogs();

  private:
    /* Private variables */
    FTimerHandle TimerHandle;

    /* Private functions */
    void SpawnLog();

    void SetRandomLocation();

    int32 GetRandIndex();

    void ChangeParamsOverTime();
};
