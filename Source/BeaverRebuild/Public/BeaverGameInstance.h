// Copyright (c) 2024 Allure Games.

#pragma once

#include "Widgets/WardrobeMenuWidget.h"
#include "Libs/BeaverTypes.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AchivementManager.h"

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

    /* Public variables*/
    FName MenuLevelName = "MenuLevel";

    uint8 HatType   = HatType | EItemTypes::Classic;
    uint8 BodyType  = BodyType | EItemTypes::Classic;
    uint8 LevelType = LevelType | EItemTypes::Classic;

    FOnBuyItemSignature OnBuyItem;

    uint8 HatSkins;
    uint8 BodySkins;
    uint8 LevelSkins;

    /* Public functions*/
    virtual void AddSlivers(int32 SliversAmount);

    UFUNCTION(BlueprintCallable)
    int GetSlivers() const
    {
        return Slivers;
    }

    void SetSlivers(int32 Value)
    {
        Slivers = Value;
    }

    const FName& GetCurrentLevel() const
    {
        return CurrentLevel;
    }

    void SetCurrentLevel(const FName& LevelName)
    {
        CurrentLevel = LevelName;
    }

    UPROPERTY()
    UAchivementManager* achivementManager;

    void linkLog(ABeaverLog* Log);
    void linkBeaver(APlayerBeaver* Beaver);

    UFUNCTION()
    void startCounStatistic();

  protected:
    UPROPERTY(EditDefaultsOnly)
    class USoundClass* GameMusicSoundClass;

    UPROPERTY(EditDefaultsOnly)
    USoundClass* GameplaySoundClass;

  private:
    /* Private variables*/
    UPROPERTY()
    class UBeaverSaveGame* SaveSlot;

    FName CurrentLevel = "GameLevel";

    int32 Slivers = 0;

    float GameMusicVolume     = 0.5;
    float GameplaySoundVolume = 0.5;

    /* Private functions*/
    void OnStart() override;

    void Shutdown() override;

    void LoadData();

    void SaveData();
};
