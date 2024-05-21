// Copyright (c) 2024 Allure Games.

#include "BeaverGameHUD.h"
#include "BeaverGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/WardrobeMenuWidget.h"

ABeaverGameHUD::ABeaverGameHUD()
{
}

void ABeaverGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EBeaverGameState::PauseMenu, CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
    GameWidgets.Add(EBeaverGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EBeaverGameState::OptionsMenu, CreateWidget<UUserWidget>(GetWorld(), OptionsMenuWidgetClass));
    GameWidgets.Add(EBeaverGameState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverMenuWidgetClass));
    GameWidgets.Add(EBeaverGameState::WardrobeMenu, CreateWidget<UUserWidget>(GetWorld(), WardrobeWidgetClass));

    if (GetWorld())
    {
        ABeaverGameMode* GameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());

        if (GameMode)
        {
            GameMode->OnGameStateChange.AddUObject(this, &ABeaverGameHUD::OnGameStateChanged);
        } 
    }
}

void ABeaverGameHUD::OnGameStateChanged(EBeaverGameState State)
{
    if (CurrentWidget)
    {
        if (State == EBeaverGameState::PauseMenu)
        {
            CurrentWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
        }

        if (!CurrentWidget->IsA<UWardrobeMenuWidget>())
        {
            CurrentWidget->RemoveFromParent();
        }
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->AddToViewport();
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->SetKeyboardFocus();
    }
}
