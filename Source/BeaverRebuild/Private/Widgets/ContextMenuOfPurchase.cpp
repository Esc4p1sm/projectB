// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/ContextMenuOfPurchase.h"
#include "Components/Button.h"
#include "Widgets/SkinsItemWidget.h"
#include "Widgets/DisadvantageSliversContext.h"
#include "BeaverGameInstance.h"
#include "Components/Image.h"

void UContextMenuOfPurchase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    ConfirmButton->OnClicked.AddDynamic(this, &UContextMenuOfPurchase::OnConfirm);
    RejectButton->OnClicked.AddDynamic(this, &UContextMenuOfPurchase::OnReject);

    NotificationWidget = CreateWidget<UDisadvantageSliversContext>(GetWorld(), NotEnoughtSliversWidgetClass);
    NotificationWidget->SetCachedMenuOfPurchase(this);

    this->SetIsFocusable(true);
}

void UContextMenuOfPurchase::OnConfirm()
{
    auto const GameInstance = StaticCast<UBeaverGameInstance*>(GetWorld()->GetGameInstance());

    if (!GameInstance)
        return;

    int32 NewSliversValue = GameInstance->GetSlivers() - SkinsItemWidget->SkinRowData.Price;

    if (NewSliversValue >= 0)
    {
        switch (SkinsItemWidget->SkinRowData.Category)
        {
        case EItemTypes::BodyType:
            GameInstance->BodyType |= SkinsItemWidget->SkinRowData.Type;
            break;

        case EItemTypes::HatType:
            GameInstance->HatType |= SkinsItemWidget->SkinRowData.Type;
            break;

        case EItemTypes::LevelType:
            GameInstance->LevelType |= SkinsItemWidget->SkinRowData.Type;
            break;
        }

        SkinsItemWidget->LockIdentifier->SetVisibility(ESlateVisibility::Collapsed);

        GameInstance->SetSlivers(NewSliversValue);
        GameInstance->OnBuyItem.Broadcast();

        SetWardrobeWidgetVisibility();

        this->RemoveFromParent();
    }
    else
    {
        AddToViewportNotificationWidget();
    }
}

FReply UContextMenuOfPurchase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    Super::NativeOnKeyDown(InGeometry, InKeyEvent);

    if (InKeyEvent.GetKey() == EKeys::P)
    {
        this->RemoveFromParent();
    }

    return FReply::Handled();
}

FReply UContextMenuOfPurchase::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

    RejectButton->SetKeyboardFocus();

    return FReply::Handled();
}

void UContextMenuOfPurchase::OnReject()
{
    SetWardrobeWidgetVisibility();

    this->RemoveFromParent();
}

void UContextMenuOfPurchase::SetWardrobeWidgetVisibility()
{
    CachedWardrobeWidget->SetVisibility(ESlateVisibility::Visible);
    CachedWardrobeWidget->SetKeyboardFocus();
}

void UContextMenuOfPurchase::AddToViewportNotificationWidget()
{
    if (NotificationWidget)
    {
        NotificationWidget->AddToViewport();
        NotificationWidget->SetKeyboardFocus();
    }
}

void UContextMenuOfPurchase::NativeDestruct()
{
    SetWardrobeWidgetVisibility();

    this->RemoveFromParent();
}