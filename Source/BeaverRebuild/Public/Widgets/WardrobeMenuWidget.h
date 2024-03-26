// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
	bool Initialize() override;
};
