// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverGameMode.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

ABeaverGameMode::ABeaverGameMode()
{
    beaverLifeTime = 40;
    beaverScore    = 0;
}

void ABeaverGameMode::BeginPlay()
{
    GetWorldTimerManager().SetTimer(lifeTimerHandle, this, &ABeaverGameMode::DecreaseLifeTime, 1, true);
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