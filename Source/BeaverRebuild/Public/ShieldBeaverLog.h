// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "BeaverLog.h"
#include "ShieldBeaverLog.generated.h"

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API AShieldBeaverLog : public ABeaverLog
{
    GENERATED_BODY()

  protected:
    void BeginPlay() override;
    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class ABeaverShield> Shield;

  private:
    /*Private variables*/
    UPROPERTY()
    class APlayerBeaver* PlayerBeaver = nullptr;
};
