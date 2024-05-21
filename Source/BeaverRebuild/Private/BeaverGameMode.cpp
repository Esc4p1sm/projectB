// Copyright (c) 2024 Allure Games.

#include "BeaverGameMode.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "BeaverPlayerController.h"
#include "Widgets/WardrobeTrigger.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ABeaverGameMode::ABeaverGameMode()
{
    PlayerControllerClass = ABeaverPlayerController::StaticClass();
    AudioComponent        = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioCmoponent"));
}

void ABeaverGameMode::SetGameState(EBeaverGameState State)
{
    if (State == GameState)
    {
        return;
    }

    GameState = State;

    if (OnGameStateChange.IsBound())
    {
        OnGameStateChange.Broadcast(GameState);
    }
}

void ABeaverGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void ABeaverGameMode::StartPlay()
{
    Super::StartPlay();

    if (MenuSoundCue)
    {
        SetCurrentGameMusic(MenuSoundCue);
    }

    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    SetGameState(EBeaverGameState::InProgress);
}

void ABeaverGameMode::StartGame()
{
    GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ABeaverGameMode::DecreaseLifeTime, 1, true);

    LogSpawner->StartSpawn();
}

void ABeaverGameMode::DecreaseLifeTime()
{
    --BeaverLifeTime;
    // GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Game Timer: %lld"), beaverLifeTime));
    OnLifeTimerUpdated.Broadcast(BeaverLifeTime);

    if (BeaverLifeTime <= 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Time out"));
        LifeTimerHandle.Invalidate();
        FinishRound();
    }
}

void ABeaverGameMode::AddLifeTime(int32 additionalTime)
{
    BeaverLifeTime += additionalTime;
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Added Time: %lld"), additionalTime));
    OnLifeTimerUpdated.Broadcast(BeaverLifeTime);
}

void ABeaverGameMode::AddScore(int32 scoreAmount)
{
    BeaverScore += scoreAmount;
    // GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Score: %lld"), beaverScore));
    OnScoreUpdated.Broadcast(BeaverScore);
}

void ABeaverGameMode::AddBeaver(APlayerBeaver* Beaver)
{
    BeaverPawn = Beaver;
}

bool ABeaverGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (PauseSet)
    {
        SetGameState(EBeaverGameState::PauseMenu);
    }

    return PauseSet;
}

bool ABeaverGameMode::ClearPause()
{
    const bool pauseCleared = Super::ClearPause();

    if (pauseCleared && WardrobeTrigger->bIsInWardrobe)
    {
        SetGameState(EBeaverGameState::WardrobeMenu);
    }

    if (pauseCleared && !WardrobeTrigger->bIsInWardrobe)
    {
        SetGameState(EBeaverGameState::InProgress);
    }

    return pauseCleared;
}

void ABeaverGameMode::SetCurrentGameMusic(USoundCue* SoundCue)
{
    if (AudioComponent)
    {
        AudioComponent->SetSound(SoundCue);
    }
}