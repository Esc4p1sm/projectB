// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Libs/BeaverTypes.h"
#include "CoreMinimal.h"
#include "Widgets/BaseUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "SkinsItemWidget.generated.h"


/**
 *
 */
UCLASS()
class BEAVERREBUILD_API USkinsItemWidget : public UBaseUserWidget
{
    GENERATED_BODY()

  public:
    FSkinsData SkinRowData;

    UPROPERTY(BlueprintReadOnly)//meta = (BindWidget))
    class UImage* LockIdentifier;

    float GetSizeBoxWidth();

    float GetSizeBoxHeight();

    void SetItemData();
    void SetSizeOfSizeBox(float Width, float Height);
  
  protected:
    void NativeOnInitialized() override;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* SkinSelectButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* SkinNameTextBlock;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class USizeBox* ItemSizeBox;

    UPROPERTY()
    class UContextMenuOfPurchase* PurchaseMenu;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UContextMenuOfPurchase> PurchaseContextMenuClass;

    UPROPERTY(EditAnywhere)
    FDataTableRowHandle DataTableRow;

  private:
    TWeakObjectPtr<class APlayerBeaver> PlayerBeaver;

    TWeakObjectPtr<class UBeaverGameInstance> GameInstance;

    TWeakObjectPtr<class ABeaverGameHUD> GameHUD;

    bool bIsItemPurchased = false;

    void ShowMenuOfPurchase();

    UFUNCTION()
    void OnSkinItemClicked();
};
