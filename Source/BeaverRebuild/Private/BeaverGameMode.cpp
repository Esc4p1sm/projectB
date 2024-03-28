// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverGameMode.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "BeaverPlayerController.h"

ABeaverGameMode::ABeaverGameMode()
{
    beaverLifeTime = 40;
    beaverScore    = 0;
    PlayerControllerClass = ABeaverPlayerController::StaticClass();
}

void ABeaverGameMode::SetGameState(EBeaverGameState state)
{
    if (state == gameState) return;
    
    gameState = state;

    onGameStateChange.Broadcast(gameState);
}

void ABeaverGameMode::BeginPlay()
{
   
}

void ABeaverGameMode::StartPlay()
{
    Super::StartPlay();

    SetGameState(EBeaverGameState::InProgress);
}

void ABeaverGameMode::StartGame()
{
    GetWorldTimerManager().SetTimer(lifeTimerHandle, this, &ABeaverGameMode::DecreaseLifeTime, 1, true);
    logSpawner->StartSpawn();
}

void ABeaverGameMode::DecreaseLifeTime()
{
    --beaverLifeTime;
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Game Timer: %lld"), beaverLifeTime));
    if (beaverLifeTime <= 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Beaver is expired"));

        FinishRound();
    }
}

void ABeaverGameMode::AddLifeTime(int32 additionalTime)
{
    beaverLifeTime += additionalTime;
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Added Time: %lld"), additionalTime));
}

void ABeaverGameMode::AddScore(int32 scoreAmount)
{
    beaverScore += scoreAmount;
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Score: %lld"), beaverScore));
}

void ABeaverGameMode::AddBeaver(APlayerBeaver *beaver)
{
    beaverPawn = beaver;
}

bool ABeaverGameMode::SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate)
{
    const bool pauseSet = Super::SetPause(PC,CanUnpauseDelegate);

    if (pauseSet)
    {
        SetGameState(EBeaverGameState::PauseMenu);
    }

    return pauseSet;
}

bool ABeaverGameMode::ClearPause()
{
    const bool pauseCleared = Super::ClearPause();

    if (pauseCleared)
    {
        SetGameState(EBeaverGameState::InProgress);
    }

    return pauseCleared;
}
