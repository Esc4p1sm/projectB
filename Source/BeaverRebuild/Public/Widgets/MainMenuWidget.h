// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERREBUILD_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:
    bool Initialize() override;

    UFUNCTION()
	void OnOpenOptionsMenu();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> optionsMenuWidgetClass;

    UPROPERTY(meta=(BindWidget))
    class UButton *optionsButton;
};
