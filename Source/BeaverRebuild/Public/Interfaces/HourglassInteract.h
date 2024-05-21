// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HourglassInteract.generated.h"

UINTERFACE(MinimalAPI)
class UHourglassInteract : public UInterface
{
    GENERATED_BODY()
};

class BEAVERREBUILD_API IHourglassInteract
{
    GENERATED_BODY()

  public:
    virtual  FVector GetDireaction() = 0;
};
