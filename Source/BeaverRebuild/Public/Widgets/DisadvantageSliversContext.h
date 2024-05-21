// Copyright (c) 2024 Allure Games.

#pragma once

#include "Widgets/ContextMenuOfPurchase.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DisadvantageSliversContext.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API UDisadvantageSliversContext : public UUserWidget
{
    GENERATED_BODY()

  public:
    void SetCachedMenuOfPurchase(UContextMenuOfPurchase* Widget)
    {
        CachedMenuOfPurchase = Widget;
    }
    
  protected:
    UPROPERTY(BlueprintReadOnly)
    TWeakObjectPtr<UContextMenuOfPurchase> CachedMenuOfPurchase;
};
