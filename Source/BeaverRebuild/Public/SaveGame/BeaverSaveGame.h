// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Libs/BeaverTypes.h"
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

    UPROPERTY(SaveGame)
    int32 SavedSlivers = 0;

    UPROPERTY(SaveGame)
    uint8 SavedHatType = 0;

    UPROPERTY(SaveGame)
    uint8 SavedBodyType = 0;

    UPROPERTY(SaveGame)
    uint8 SavedLevelType = 0;

    UPROPERTY(SaveGame)
    float SavedGameMusicVolume = 0;

    UPROPERTY(SaveGame)
    float SavedGameplaySoundVolume = 0;
};
