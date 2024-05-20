// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverPlayerController.h"
#include "BeaverGameMode.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/NavigationConfig.h"

ABeaverPlayerController::ABeaverPlayerController()
{
    
}

void ABeaverPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        ABeaverGameMode* GameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());

        if (GameMode)
        {
            GameMode->OnGameStateChange.AddUObject(this, &ABeaverPlayerController::OnGameStateChanged);
        }
    }
}

void ABeaverPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent)
    {
        return;
    }

    InputComponent->BindAction("MainMenu", IE_Pressed, this, &ABeaverPlayerController::OnPauseGame);
}

void ABeaverPlayerController::OnGameStateChanged(EBeaverGameState State)
{
    if (State == EBeaverGameState::InProgress)
    {
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    }
    else
    {
        bShowMouseCursor = true;
        SetInputMode(FInputModeUIOnly());
        ChangeMenuNavigation();
    }
}

void ABeaverPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
    {
        return;
    }

    if (!bGameIsPause)
    {
        GetWorld()->GetAuthGameMode()->SetPause(this);

        bGameIsPause                                           = true;
        InputComponent->GetActionBinding(0).bExecuteWhenPaused = true;
    }
    else if (bGameIsPause)
    {
        GetWorld()->GetAuthGameMode()->ClearPause();
        bGameIsPause = false;
    }
}

void ABeaverPlayerController::ChangeMenuNavigation()
{
    FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::A, EUINavigation::Left);
    FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);
    FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::W, EUINavigation::Up);
    FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::D, EUINavigation::Right);
}