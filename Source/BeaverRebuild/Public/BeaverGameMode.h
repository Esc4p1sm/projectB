// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerBeaver.h"
#include "CoreMinimal.h"
#include "LogSpawner.h"
#include "GameFramework/GameMode.h"
#include "BeaverGameMode.generated.h"

UCLASS()
class BEAVERREBUILD_API ABeaverGameMode : public AGameMode
{
	GENERATED_BODY()
	
  public:
    ABeaverGameMode();

    virtual void DecreaseLifeTime();

    virtual void AddScore(int32 scoreAmount);

    void AddBeaver(class APlayerBeaver *beaver);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void FinishRound();

    UFUNCTION(BlueprintCallable)
    virtual void AddLifeTime(int32 additionalTime);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player info")
    int32 beaverScore;
    
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    FTimerHandle lifeTimerHandle;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player info")
    int32 beaverLifeTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner info")
    ALogSpawner* logSpawner;

  protected:    
    virtual void BeginPlay() override;

    UPROPERTY()
    APlayerBeaver *beaverPawn;

   
};
