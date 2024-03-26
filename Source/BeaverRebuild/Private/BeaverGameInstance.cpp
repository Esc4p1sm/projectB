// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/BeaverSaveGame.h"
#include "GameFramework/GameUserSettings.h"

UBeaverGameInstance::UBeaverGameInstance()
{
    slivers = 0;
    menuLevel = "MenuLevel";
}

void UBeaverGameInstance::OnStart()
{
    LoadSlivers();

    if (GetWorld())
    {
        FLatentActionInfo actioninfo;
        UGameplayStatics::LoadStreamLevel(GetWorld(), menuLevel, true, false, actioninfo);
    }

    //UGameUserSettings::GetGameUserSettings()->LoadSettings();
    saveSlot = StaticCast<UBeaverSaveGame *>(UGameplayStatics::CreateSaveGameObject(UBeaverSaveGame::StaticClass()));
    
}

void UBeaverGameInstance::Shutdown()
{
    SaveSlivers();
    UGameUserSettings::GetGameUserSettings()->SaveSettings();
    Super::Shutdown();
}

void UBeaverGameInstance::AddSlivers(int32 sliversAmount)
{
    slivers += sliversAmount;
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Slivers: %lld"), slivers));
}

void UBeaverGameInstance::LoadSlivers()
{
    //UBeaverSaveGame *saveSlot = StaticCast<UBeaverSaveGame*>(UGameplayStatics::CreateSaveGameObject(UBeaverSaveGame::StaticClass()));

    saveSlot = StaticCast<UBeaverSaveGame*>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot1"), 0));

    if (saveSlot) this->slivers = saveSlot->savedSlivers;
    
}

void UBeaverGameInstance::SaveSlivers()
{
    //UBeaverSaveGame *saveSlot = StaticCast<UBeaverSaveGame*>(UGameplayStatics::CreateSaveGameObject(UBeaverSaveGame::StaticClass()));

    if (saveSlot)
    {
        saveSlot->savedSlivers = this->slivers;
        UGameplayStatics::SaveGameToSlot(saveSlot, TEXT("SaveSlot1"), 0);
    }
}


