// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERREBUILD_API UOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
    bool Initialize() override;

    UFUNCTION()
    void OnBackToMenu();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> mainMenuWidgetClass;

	UPROPERTY(meta = (BindWidget))
    class UButton *backToMenuButton;
};
