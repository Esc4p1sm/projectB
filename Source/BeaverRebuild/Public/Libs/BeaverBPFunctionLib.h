// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeaverBPFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERREBUILD_API UBeaverBPFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

  public:

    UFUNCTION(BlueprintCallable)
	static FVector MakeRandomDirection(float minAngle, float maxAngle);
};
