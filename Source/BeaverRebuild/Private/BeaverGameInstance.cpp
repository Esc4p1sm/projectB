// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/BeaverSaveGame.h"

UBeaverGameInstance::UBeaverGameInstance()
{
    slivers = 0;
}

void UBeaverGameInstance::OnStart()
{
    LoadSlivers();
}

void UBeaverGameInstance::Shutdown()
{
    SaveSlivers();

    Super::Shutdown();
}

void UBeaverGameInstance::AddSlivers(int32 sliversAmount)
{
    slivers += sliversAmount;
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Slivers: %lld"), slivers));
}

void UBeaverGameInstance::LoadSlivers()
{
    UBeaverSaveGame *saveSlot = Cast<UBeaverSaveGame>(UGameplayStatics::CreateSaveGameObject(UBeaverSaveGame::StaticClass()));

    saveSlot = Cast<UBeaverSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot1"), 0));

    if (IsValid(saveSlot)) this->slivers = saveSlot->savedSlivers;
    
}

void UBeaverGameInstance::SaveSlivers()
{
    UBeaverSaveGame *saveSlot = Cast<UBeaverSaveGame>(UGameplayStatics::CreateSaveGameObject(UBeaverSaveGame::StaticClass()));

    if (IsValid(saveSlot))
    {
        saveSlot->savedSlivers = this->slivers;
        UGameplayStatics::SaveGameToSlot(saveSlot, TEXT("SaveSlot1"), 0);
    }
}


