// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BeaverLog.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Interfaces/HourglassInteract.h"
#include "LogSpawner.generated.h"


USTRUCT(BlueprintType)
struct FSpawnerParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector spawnerLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float spawnRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float stdChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float rateChange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 spawnRangeLeft;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 spawnRangeRight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 distBetweenLogs;  
};


USTRUCT(BlueprintType)
struct FSpawningLogParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float minAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float maxAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float initialSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float speedChange;
};


UCLASS()
class BEAVERREBUILD_API ALogSpawner : public AActor/*, public IHourglassInteract*/
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
    TArray<TSubclassOf<class ABeaverLog>> listOfLogs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner parameters")
    FSpawnerParameters spawnParams;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning log parameters")
    FSpawningLogParameters spawnLogParams;

    /* Public functions */
    UFUNCTION(BlueprintCallable)
    void StopSpawn();

    UFUNCTION(BlueprintCallable)
    void StartSpawn();

    UFUNCTION(BlueprintCallable)
    void DestroyAllLogs();

  private:
    /* Private variables */
   // UPROPERTY()
    //float slowdownScale;

    UPROPERTY()
    FTimerHandle timerHandle;

    /* Private functions */
    void SpawnLog();

   /* FVector MakeRandomDirection();*/

    void SetRandomLocation();

    TSubclassOf<ABeaverLog> RandomizerOfLogs();

    void ChangeParamsOverTime();

    /* Getters and setters */
    //float &GetSlowdownScale() override { return slowdownScale; }
    /* FVector GetDireaction() override
    {
        return MakeRandomDirection();
    }*/

   // float &GetSpawnRate() override { return spawnParams.spawnRate; }

};
