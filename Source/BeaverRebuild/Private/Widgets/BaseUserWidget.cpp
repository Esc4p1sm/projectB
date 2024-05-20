// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/BaseUserWidget.h"
#include "BeaverPlayerController.h"

void UBaseUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    const auto PlayerController = StaticCast<ABeaverPlayerController*>(GetWorld()->GetFirstPlayerController());

    if (!PlayerController) return;

    OnCloseUserWidget.AddUObject(PlayerController, &ABeaverPlayerController::OnPauseGame);
}

void UBaseUserWidget::NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath,
                                            const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusChanging(PreviousFocusPath, NewWidgetPath, InFocusEvent);

    PreviousFocusedWidget = PreviousFocusPath.GetLastWidget();
}

FReply UBaseUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    Super::NativeOnKeyDown(InGeometry,InKeyEvent);

    if (InKeyEvent.IsRepeat())
    {
        return FReply::Unhandled();
    }

    if (InKeyEvent.GetKey() == EKeys::P)
    {
        const auto PlayerController = StaticCast<ABeaverPlayerController*>(GetWorld()->GetFirstPlayerController());

        if (!PlayerController) return FReply::Unhandled();

        if (OnCloseUserWidget.IsBound())
        {
            OnCloseUserWidget.Broadcast();
        }
    }

    return FReply::Handled();
}

FReply UBaseUserWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusReceived(InGeometry,InFocusEvent);

    if (!PreviousFocusedWidget.IsValid())
    {
        return FReply::Unhandled();
    }

    FSlateApplication::Get().SetKeyboardFocus(PreviousFocusedWidget.Pin());

    PreviousFocusedWidget.Reset();

    return FReply::Handled();
}

void UBaseUserWidget::NativeDestruct()
{
    OnCloseUserWidget.Clear();

    Super::NativeDestruct();
}
