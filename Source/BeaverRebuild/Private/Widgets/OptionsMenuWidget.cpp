// Copyright (c) 2024 Allure Games.

#include "Widgets/OptionsMenuWidget.h"
#include "Components/Button.h"
#include "BeaverGameMode.h"
#include "BeaverPlayerController.h"

bool UOptionsMenuWidget::Initialize()
{
    const bool InitStatus = Super::Initialize();

    if (InitStatus)
    {
        BackToMenuButton->OnClicked.AddDynamic(this, &UOptionsMenuWidget::OnBackToMenu);
        this->SetIsFocusable(true);
    }

    return InitStatus;
}

void UOptionsMenuWidget::OnBackToMenu()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
    {
        return;
    }

    ABeaverGameMode* GameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());

    GameMode->SetGameState(EBeaverGameState::PauseMenu);
}
