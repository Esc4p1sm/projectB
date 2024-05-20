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

    void OnGameStateChanged(EBeaverGameState State);

    const TMap<EBeaverGameState, UUserWidget*>& GetGameWidgets() const
    {
        return GameWidgets;
    }

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> OptionsMenuWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> GameOverMenuWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> WardrobeWidgetClass;

    UPROPERTY()
    TMap<EBeaverGameState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;
};
