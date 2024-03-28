// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/WardrobeMenuWidget.h"
#include "Libs/BeaverTypes.h"
#include "Components/Button.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Curves/CurveFloat.h"
#include "PlayerBeaver.h"
#include "Widgets/WardrobeTrigger.h"

bool UWardrobeMenuWidget::Initialize()
{
    const bool initStatus = Super::Initialize();
    
    if (initStatus)
    {
        backToGameButton->OnClicked.AddDynamic(this, &UWardrobeMenuWidget::OnBackToGame);
    }
    return initStatus;
}

void UWardrobeMenuWidget::OnBackToGame()
{
    Cast<ABeaverGameMode>(GetWorld()->GetAuthGameMode())->SetGameState(EBeaverGameState::InProgress);
   
    this->RemoveFromViewport();
}


