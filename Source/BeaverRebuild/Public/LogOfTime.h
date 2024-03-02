// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaverLog.h"
#include "LogOfTime.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API ALogOfTime : public ABeaverLog
{
    GENERATED_BODY()

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object for spawn")
    TSubclassOf<class AHourglass> hourglass;

    /* Public functions*/
    //void MarkAsJumped() override;

  private:
    /* Private functions*/
    void SpawnHourglass();
    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
