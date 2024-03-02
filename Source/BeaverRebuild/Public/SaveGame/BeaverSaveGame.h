// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BeaverSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERREBUILD_API UBeaverSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	public:
    UBeaverSaveGame();

    UPROPERTY()
    int32 savedSlivers;
    
};
