// Copyright (c) 2024 Allure Games.

#include "Widgets/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BeaverGameMode.h"
#include "BeaverPlayerController.h"

bool UMainMenuWidget::Initialize()
{
    const bool InitStatus = Super::Initialize();

    if (InitStatus)
    {
        OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOpenOptionsMenu);
        BackToGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnBackToGame);
        this->SetIsFocusable(true);
    }

    return InitStatus;
}

void UMainMenuWidget::OnOpenOptionsMenu()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
    {
        return;
    }

    ABeaverGameMode* GameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());

    GameMode->SetGameState(EBeaverGameState::OptionsMenu);
}

void UMainMenuWidget::OnBackToGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
    {
        return;
    }

    const auto PlayerController = StaticCast<ABeaverPlayerController*>(GetWorld()->GetFirstPlayerController());

    if (PlayerController)
    {
        PlayerController->bGameIsPause = false;
    }

    GetWorld()->GetAuthGameMode()->ClearPause();
}
