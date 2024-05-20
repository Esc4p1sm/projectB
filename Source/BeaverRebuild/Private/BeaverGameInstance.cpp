// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/BeaverSaveGame.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"

UBeaverGameInstance::UBeaverGameInstance()
{
}

void UBeaverGameInstance::linkLog(ABeaverLog *Log)
{
    Log->OnLogScored.AddDynamic(this->achivementManager, &UAchivementManager::CountLogStats);
    //GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Log linked")));
}

void UBeaverGameInstance::linkBeaver(APlayerBeaver *Beaver)
{
    Beaver->OnBeaverStateChanged.AddDynamic(this->achivementManager, &UAchivementManager::CountBeaverStats);
}

void UBeaverGameInstance::startCounStatistic()
{

}

void UBeaverGameInstance::OnStart()
{
    LoadData();

    if (GameplaySoundClass && GameMusicSoundClass)
    {
        GameplaySoundClass->Properties.Volume = GameplaySoundVolume;
        GameMusicSoundClass->Properties.Volume = GameMusicVolume;
    }

    if (GetWorld())
    {
        achivementManager = NewObject<UAchivementManager>(this);

        FLatentActionInfo actioninfo;

        UGameplayStatics::LoadStreamLevel(GetWorld(), MenuLevelName, true, false, actioninfo);
        achivementManager->setSkins(HatSkins, BodySkins, LevelSkins);
        achivementManager->world = GetWorld();
    }

    SaveSlot = StaticCast<UBeaverSaveGame*>(UGameplayStatics::CreateSaveGameObject(UBeaverSaveGame::StaticClass()));
}

void UBeaverGameInstance::Shutdown()
{
    Super::Shutdown();

    if (GameplaySoundClass && GameMusicSoundClass)
    {
        GameplaySoundVolume = GameplaySoundClass->Properties.Volume;
        GameMusicVolume     = GameMusicSoundClass->Properties.Volume; 
    }

    SaveData();

    UGameUserSettings::GetGameUserSettings()->SaveSettings();
}

void UBeaverGameInstance::AddSlivers(int32 SliversAmount)
{
    Slivers += SliversAmount;

    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Slivers: %lld"), Slivers));
}

void UBeaverGameInstance::LoadData()
{
    SaveSlot = StaticCast<UBeaverSaveGame*>(UGameplayStatics::LoadGameFromSlot(TEXT("AutoSaveSlot"), 0));

    if (SaveSlot)
    {
        Slivers              = SaveSlot->SavedSlivers;
        HatType              = SaveSlot->SavedHatType;
        BodyType             = SaveSlot->SavedBodyType;
        LevelType            = SaveSlot->SavedLevelType;
        GameplaySoundVolume  = SaveSlot->SavedGameplaySoundVolume;
        GameMusicVolume      = SaveSlot->SavedGameMusicVolume;
    }
}

void UBeaverGameInstance::SaveData()
{
    if (SaveSlot)
    {
        SaveSlot->SavedHatType              = HatType;
        SaveSlot->SavedBodyType             = BodyType;
        SaveSlot->SavedLevelType            = LevelType;
        SaveSlot->SavedSlivers              = Slivers;
        SaveSlot->SavedGameplaySoundVolume  = GameplaySoundVolume;
        SaveSlot->SavedGameMusicVolume      = GameMusicVolume;

        UGameplayStatics::SaveGameToSlot(SaveSlot, TEXT("AutoSaveSlot"), 0);
    }
}
