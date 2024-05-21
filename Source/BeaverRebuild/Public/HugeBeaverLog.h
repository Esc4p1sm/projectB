// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "BeaverLog.h"
#include "HugeBeaverLog.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API AHugeBeaverLog : public ABeaverLog
{
    GENERATED_BODY()

  public:
    AHugeBeaverLog();

    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RangeBtwnLogs = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear)
    TSubclassOf<class ABeaverLog> StdLogs;

    UFUNCTION()
    void SpawnLogs();
};
