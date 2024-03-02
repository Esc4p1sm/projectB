// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaverLog.h"
#include "GoldenBeaverLog.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API AGoldenBeaverLog : public ABeaverLog
{
    GENERATED_BODY()

  public:
    void BeginPlay() override;
    void BeaverLogSlivers() override;
  
};
