// Fill out your copyright notice in the Description page of Project Settings.


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

    gameWidgets.Add(EBeaverGameState::PauseMenu,CreateWidget<UUserWidget>(GetWorld(),mainMenuWidgetClass));
    gameWidgets.Add(EBeaverGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), playerHUDWidgetClass));
    gameWidgets.Add(EBeaverGameState::PauseOptions, CreateWidget<UUserWidget>(GetWorld(), optionsMenuWidgetClass));
    gameWidgets.Add(EBeaverGameState::GameOver, CreateWidget<UUserWidget>(GetWorld(), gameOverMenuWidgetClass));
    gameWidgets.Add(EBeaverGameState::WardrobeMenu,CreateWidget<UUserWidget>(GetWorld(),wardrobeWidgetClass));

    if (GetWorld())
    {
        ABeaverGameMode *gameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());

        if (IsValid(gameMode))
        {
            gameMode->onGameStateChange.AddUObject(this, &ABeaverGameHUD::OnGameStateChanged);
        }
    }
}

void ABeaverGameHUD::OnGameStateChanged(EBeaverGameState state)
{
    if (currentWidget)
    {
        if (!currentWidget->IsA<UWardrobeMenuWidget>())
        {
            currentWidget->RemoveFromViewport();
        }    
    } 
     
    if (gameWidgets.Contains(state))
    {
        currentWidget = gameWidgets[state];
    }

    if (currentWidget)
    {
        currentWidget->AddToViewport();
    }  
}
