// Copyright (c) 2024 Allure Games.

#include "Widgets/WardrobeMenuWidget.h"
#include "BeaverGameMode.h"
#include "Libs/BeaverTypes.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/NavigationConfig.h"
#include "Widgets/SkinsItemWidget.h"
#include "Components/SizeBox.h"
#include "BeaverPlayerController.h"

bool UWardrobeMenuWidget::Initialize()
{
    const bool InitStatus = Super::Initialize();

    if (InitStatus)
    {
        BackToGameButton->OnClicked.AddDynamic(this, &UWardrobeMenuWidget::OnLeaveWardrobe);

        const auto SkinItemWidget = StaticCast<USkinsItemWidget*>(LevelItemScrollBox->GetChildAt(2));

        CachedWidthOfItemSizeBox  = SkinItemWidget->GetSizeBoxWidth();
        CachedHeightOfItemSizeBox = SkinItemWidget->GetSizeBoxHeight();
        
        ScrollBoxes = {SkinItemScrollBox, LevelItemScrollBox, HatItemScrollBox};
    }

    return InitStatus;
}

void UWardrobeMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    FSlateApplication::Get().OnApplicationPreInputKeyDownListener().AddUObject(this, &UWardrobeMenuWidget::OnKeyDown);

    BackToGameButton->SetKeyboardFocus();
}

void UWardrobeMenuWidget::OnKeyDown(const FKeyEvent& KeyEvent)
{
    if (!this->IsHovered())
    {
        return;
    }
    
    const auto FocusedScrollBoxToScroll = GetFocusedScrollBox();

    if (!FocusedScrollBoxToScroll)
    {
        return;
    }

    int32& CurrentItemIndex    = GetCurrentIndexOfFocusedScrollBox(FocusedScrollBoxToScroll);
    const int32 SavedItemIndex = CurrentItemIndex;

    if (KeyEvent.GetKey() == EKeys::S || KeyEvent.GetKey() == EKeys::Down)
    {
        CurrentItemIndex++;
    }
    else if (KeyEvent.GetKey() == EKeys::W || KeyEvent.GetKey() == EKeys::Up)
    {
        CurrentItemIndex--;
    }
    else
    {
        return;
    }

    CurrentItemIndex = FMath::Clamp(CurrentItemIndex, 1, FocusedScrollBoxToScroll->GetChildrenCount() - 2);

    UpdateItemSize(CurrentItemIndex, SavedItemIndex, FocusedScrollBoxToScroll);
}

void UWardrobeMenuWidget::UpdateItemSize(int32 NewIndex, int32 PreviousIndex,const UScrollBox* FocusedScrollBoxToScroll)
{
    const auto CurrentItemWidget  = StaticCast<USkinsItemWidget*>(FocusedScrollBoxToScroll->GetChildAt(NewIndex));
    const auto PreviousItemWidget = StaticCast<USkinsItemWidget*>(FocusedScrollBoxToScroll->GetChildAt(PreviousIndex));

    if (!PreviousItemWidget || !CurrentItemWidget)
    {
        return;
    }

    PreviousItemWidget->SetSizeOfSizeBox(CachedWidthOfItemSizeBox * 0.5, CachedHeightOfItemSizeBox * 0.5);
    PreviousItemWidget->SetIsEnabled(false);

    CurrentItemWidget->SetSizeOfSizeBox(CachedWidthOfItemSizeBox, CachedHeightOfItemSizeBox);
    CurrentItemWidget->SetIsEnabled(true);
}

const UScrollBox* UWardrobeMenuWidget::GetFocusedScrollBox() const
{
    for (const UScrollBox* ScrollBox : ScrollBoxes)
    {
        if (ScrollBox->HasFocusedDescendants())
        {
            return ScrollBox;
        }
    }
    
    return nullptr;
}

int32& UWardrobeMenuWidget::GetCurrentIndexOfFocusedScrollBox(const UScrollBox* FocusedScrollBox)
{
    if (FocusedScrollBox == SkinItemScrollBox)
    {
        return IndexSkinScrollBox;
    }
    else if (FocusedScrollBox == HatItemScrollBox)
    {
        return IndexHatScrollBox;
    }
    else if (FocusedScrollBox == LevelItemScrollBox)
    {
        return IndexLevelScrollBox;
    }
    else
    {
        return InvalidIndex;
    }
}

void UWardrobeMenuWidget::OnLeaveWardrobe()
{
    auto const GameMode = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());

    if (GameMode)
    {
        GameMode->OnBackToGame.Broadcast();

        this->RemoveFromParent();
    }
}

FReply UWardrobeMenuWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
   Super::OnFocusReceived(InGeometry,InFocusEvent);

   if (this->IsHovered())
   {
        FSlateApplication::Get().SetKeyboardFocus(Super::GetPreviousFocusedWidget().Pin());

        Super::GetPreviousFocusedWidget().Reset();
   }
   else
   {
        BackToGameButton->SetKeyboardFocus();
   }

   return FReply::Handled();
}

void UWardrobeMenuWidget::NativeDestruct()
{
   FSlateApplication::Get().OnApplicationPreInputKeyDownListener().Clear();
   
   Super::NativeDestruct();
}