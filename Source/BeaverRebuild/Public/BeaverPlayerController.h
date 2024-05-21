// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Libs/BeaverTypes.h"
#include "BeaverPlayerController.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API ABeaverPlayerController : public APlayerController
{
    GENERATED_BODY()

  public:
    ABeaverPlayerController();

    void BeginPlay() override;

    bool bGameIsPause = false;

    void OnPauseGame();

  private:
    void SetupInputComponent() override;
    void OnGameStateChanged(EBeaverGameState State);
    void ChangeMenuNavigation();
};
