// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaverLog.h"
#include "ShieldBeaverLog.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API AShieldBeaverLog : public ABeaverLog
{
    GENERATED_BODY()

  protected:
    void BeginPlay() override;
    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class ABeaverShield> shield;

  private:
    /*Private variables*/
    UPROPERTY()
    class APlayerBeaver *ptrBeaver;
};
