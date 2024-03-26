// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OptionsMenuWidget.h"
#include "Components/Button.h"
#include "BeaverGameMode.h"

bool UOptionsMenuWidget::Initialize()
{
    const bool initStatus = Super::Initialize();

    if (initStatus)
    { 
        backToMenuButton->OnClicked.AddDynamic(this,&UOptionsMenuWidget::OnBackToMenu);
    }

    return initStatus;
}

void UOptionsMenuWidget::OnBackToMenu()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    ABeaverGameMode *gameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());
    gameMode->SetGameState(EBeaverGameState::PauseMenu);
    /*auto options = CreateWidget<UUserWidget>(GetWorld(), mainMenuWidgetClass);
    this->RemoveFromViewport();
    options->AddToViewport();*/
}
