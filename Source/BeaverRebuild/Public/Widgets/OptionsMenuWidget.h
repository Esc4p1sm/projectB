// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/BaseUserWidget.h"
#include "OptionsMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API UOptionsMenuWidget : public UBaseUserWidget
{
    GENERATED_BODY()

  public:
    bool Initialize() override;

  protected:
    UFUNCTION()
    void OnBackToMenu();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

    UPROPERTY(meta = (BindWidget))
    class UButton* BackToMenuButton;
};

