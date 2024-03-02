// Fill out your copyright notice in the Description page of Project Settings.

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
    int32 rangeBtwnLogs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class ABeaverLog> stdLogs;

    UFUNCTION()
    void SpawnLogs();
};
