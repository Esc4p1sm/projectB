// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
    void SetCachedMenuOfPurchase(TWeakObjectPtr<class UContextMenuOfPurchase> Widget)
    {
        CachedMenuOfPurchase = Widget;
    }

  protected:
    UPROPERTY(BlueprintReadOnly)  
    TWeakObjectPtr<UContextMenuOfPurchase> CachedMenuOfPurchase;
};
