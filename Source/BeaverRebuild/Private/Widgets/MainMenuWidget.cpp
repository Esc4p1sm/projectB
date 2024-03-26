// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BeaverGameMode.h"

bool UMainMenuWidget::Initialize()
{
    const bool initStatus = Super::Initialize();

    if (initStatus)
    {
        optionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOpenOptionsMenu); 
    }

    return initStatus;
}

void UMainMenuWidget::OnOpenOptionsMenu()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    ABeaverGameMode *gameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());
    gameMode->SetGameState(EBeaverGameState::PauseOptions);
   /* auto options = CreateWidget<UUserWidget>(GetWorld(),optionsMenuWidgetClass);
    this->RemoveFromViewport();
    options->AddToViewport();*/
}
