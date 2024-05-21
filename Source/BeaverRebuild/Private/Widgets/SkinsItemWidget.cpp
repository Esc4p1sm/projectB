// Copyright (c) 2024 Allure Games.

#include "Widgets/SkinsItemWidget.h"
#include "PlayerBeaver.h"
#include "BeaverGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverGameHUD.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/WrapBox.h"
#include "Widgets/ContextMenuOfPurchase.h"
#include "Widgets/WardrobeMenuWidget.h"

void USkinsItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (SkinSelectButton)
    {
        SkinSelectButton->OnClicked.AddDynamic(this, &USkinsItemWidget::OnSkinItemClicked);

        SkinRowData  = *(DataTableRow.GetRow<FSkinsData>(TEXT("")));
        GameInstance = StaticCast<UBeaverGameInstance*>(GetWorld()->GetGameInstance());
        PlayerBeaver = StaticCast<APlayerBeaver*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        GameHUD      = StaticCast<ABeaverGameHUD*>(GetWorld()->GetFirstPlayerController()->GetHUD());

        if (SkinRowData.Type != EItemTypes::Classic)
        {
            ItemSizeBox->SetWidthOverride(ItemSizeBox->GetWidthOverride() * 0.5);
            ItemSizeBox->SetHeightOverride(ItemSizeBox->GetHeightOverride() * 0.5);
            this->SetIsEnabled(false);
        }

        PurchaseMenu = CreateWidget<UContextMenuOfPurchase>(GetWorld(), PurchaseContextMenuClass);

        SetItemData();
    }
}

void USkinsItemWidget::SetItemData()
{
    if (SkinNameTextBlock)
    {
        SkinNameTextBlock->SetText(FText::FromName(DataTableRow.RowName));
    }

    if (LockIdentifier)
    {
        switch (SkinRowData.Category)
        {
        case EItemTypes::BodyType:
            bIsItemPurchased = GameInstance->BodyType & SkinRowData.Type;
            break;

        case EItemTypes::HatType:
            bIsItemPurchased = GameInstance->HatType & SkinRowData.Type;
            break;

        case EItemTypes::LevelType:
            bIsItemPurchased = GameInstance->LevelType & SkinRowData.Type;
            break;
        }

        if (bIsItemPurchased)
        {
            LockIdentifier->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void USkinsItemWidget::OnSkinItemClicked()
{
    if (!GameInstance.IsValid())
    {
        return;
    }

    bool bIsBodyType  = (SkinRowData.Category == EItemTypes::BodyType)  && (GameInstance->BodyType & SkinRowData.Type);
    bool bIsHatType   = (SkinRowData.Category == EItemTypes::HatType)   && (GameInstance->HatType & SkinRowData.Type);
    bool bIsLevelType = (SkinRowData.Category == EItemTypes::LevelType) && (GameInstance->LevelType & SkinRowData.Type);

    if (bIsBodyType)
    {
        PlayerBeaver->SetBeaverSkin(SkinRowData.BeaverSkinSkeletalMesh);
    }
    else if (bIsHatType)
    {
        PlayerBeaver->SetBeaverHat(SkinRowData.HatStaticMesh);
    }
    else if (bIsLevelType)
    {
        GameInstance->SetCurrentLevel(SkinRowData.LevelName);
    }
    else
    {
        ShowMenuOfPurchase();
    }
}

void USkinsItemWidget::ShowMenuOfPurchase()
{
    if (PurchaseMenu)
    {
        auto const WardrobeWidget = StaticCast<UWardrobeMenuWidget*>(GameHUD->GetGameWidgets()[EBeaverGameState::WardrobeMenu]);
        
        PurchaseMenu->SetSkinsItemWidget(this);
        PurchaseMenu->AddToViewport();
        PurchaseMenu->SetCachedWardrobeWidget(WardrobeWidget);

        WardrobeWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
}

void USkinsItemWidget::SetSizeOfSizeBox(float Width, float Height)
{
    ItemSizeBox->SetWidthOverride(Width);
    ItemSizeBox->SetHeightOverride(Height);
}

float USkinsItemWidget::GetSizeBoxWidth()
{
    return ItemSizeBox->GetWidthOverride();
}

float USkinsItemWidget::GetSizeBoxHeight()
{
    return ItemSizeBox->GetHeightOverride();
}
