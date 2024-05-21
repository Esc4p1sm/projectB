// Copyright (c) 2024 Allure Games.

#pragma once

#include "Widgets/SkinsItemWidget.h"
#include "Widgets/WardrobeMenuWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContextMenuOfPurchase.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API UContextMenuOfPurchase : public UUserWidget
{
    GENERATED_BODY()

  public:
    void NativeOnInitialized() override;

    void SetSkinsItemWidget(class USkinsItemWidget* Widget)
    {
        SkinsItemWidget = Widget;
    }

    void SetCachedWardrobeWidget(class UWardrobeMenuWidget* Widget)
    {
        CachedWardrobeWidget = Widget;
    }

  protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* ConfirmButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UButton* RejectButton;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> NotEnoughtSliversWidgetClass;

    UPROPERTY()
    class UDisadvantageSliversContext* NotificationWidget = nullptr;

    TWeakObjectPtr<USkinsItemWidget> SkinsItemWidget;

    TWeakObjectPtr<UWardrobeMenuWidget> CachedWardrobeWidget;

    void SetWardrobeWidgetVisibility();
    void AddToViewportNotificationWidget();

    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
    virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

    UFUNCTION()
    void OnReject();

    UFUNCTION()
    void OnConfirm();
};
