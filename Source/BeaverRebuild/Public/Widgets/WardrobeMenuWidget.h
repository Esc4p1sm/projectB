// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/BaseUserWidget.h"
#include "WardrobeMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API UWardrobeMenuWidget : public UBaseUserWidget
{
    GENERATED_BODY()

  protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UButton* BackToGameButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UScrollBox* LevelItemScrollBox;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UScrollBox* HatItemScrollBox;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UScrollBox* SkinItemScrollBox;

    UPROPERTY()
    TArray<const UScrollBox*> ScrollBoxes;

    int32 IndexSkinScrollBox  = 2;
    int32 IndexHatScrollBox   = 2;
    int32 IndexLevelScrollBox = 2;
    int32 InvalidIndex  = -2;

    float CachedWidthOfItemSizeBox;
    float CachedHeightOfItemSizeBox;

    const UScrollBox* GetFocusedScrollBox() const;

    int32& GetCurrentIndexOfFocusedScrollBox(const UScrollBox* FocusedScrollBox);

    void UpdateItemSize(int32 NewIndex, int32 PreviousIndex, const UScrollBox* FocusedScrollBoxToScroll);
    void OnKeyDown(const FKeyEvent& KeyEvent);

    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
    virtual bool Initialize() override;

    UFUNCTION()
    void OnLeaveWardrobe();
};
