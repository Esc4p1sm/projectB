// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 *
 */

DECLARE_MULTICAST_DELEGATE(FOnCloseUserWidgetSignature);

UCLASS(Abstract)
class BEAVERREBUILD_API UBaseUserWidget : public UUserWidget
{
    GENERATED_BODY()

  protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
    virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
    virtual void NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath,
                                       const FFocusEvent& InFocusEvent) override;

    TWeakPtr<SWidget> GetPreviousFocusedWidget() const
    {
        return PreviousFocusedWidget;
    }

  private:
    TWeakPtr<SWidget> PreviousFocusedWidget;
    FOnCloseUserWidgetSignature OnCloseUserWidget;
};
