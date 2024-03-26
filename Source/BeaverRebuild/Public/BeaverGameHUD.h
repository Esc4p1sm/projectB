// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Libs/BeaverTypes.h"
#include "BeaverGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERREBUILD_API ABeaverGameHUD : public AHUD
{
	GENERATED_BODY()
  public:
    ABeaverGameHUD();

	void BeginPlay() override;

	void OnGameStateChanged(EBeaverGameState state);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf< UUserWidget> mainMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> playerHUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> optionsMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> gameOverMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> wardrobeWidgetClass;

	UPROPERTY()
    TMap<EBeaverGameState, UUserWidget *> gameWidgets;

	UPROPERTY()
    UUserWidget *currentWidget=nullptr;
};
