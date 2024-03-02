// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BeaverGameInstance.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API UBeaverGameInstance : public UGameInstance
{
    GENERATED_BODY()

  public:
    UBeaverGameInstance();

  public:
    /* Public variables*/
    UPROPERTY()
    int32 slivers;

    /* Public functions*/
    virtual void AddSlivers(int32 sliversAmount);

  private:
    /* Private functions*/
    void OnStart() override;
    void Shutdown() override;

    UFUNCTION()
    void LoadSlivers();

    UFUNCTION()
    void SaveSlivers();
};
