// Copyright (c) 2024 Allure Games.

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
    ALogOfTime();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object for spawn")
    TSubclassOf<class AHourglass> Hourglass;

    /* Public functions*/
    // void MarkAsJumped() override;

  private:
    /* Private functions*/
    void SpawnHourglass();
    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
