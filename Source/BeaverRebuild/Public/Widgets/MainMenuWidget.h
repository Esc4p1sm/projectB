// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/BaseUserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API UMainMenuWidget : public UBaseUserWidget
{
    GENERATED_BODY()

  public:
    bool Initialize() override;

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> optionsMenuWidgetClass;

    UPROPERTY(meta = (BindWidget))
    class UButton* OptionsButton;

    UPROPERTY(meta = (BindWidget))
    UButton* BackToGameButton;

    UFUNCTION()
    void OnOpenOptionsMenu();

    UFUNCTION()
    void OnBackToGame();
};
