// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WardrobeMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERREBUILD_API UWardrobeMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
    public:

	bool Initialize() override;

    UFUNCTION()
    void OnBackToGame();
    
	UPROPERTY(meta = (BindWidget))
    class UButton *backToGameButton;
};
