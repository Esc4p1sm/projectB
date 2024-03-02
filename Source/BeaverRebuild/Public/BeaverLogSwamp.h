// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaverLog.h"
#include "BeaverLogSwamp.generated.h"

UCLASS()
class BEAVERREBUILD_API ABeaverLogSwamp : public ABeaverLog
{
    GENERATED_BODY()

  public:
    virtual void MarkAsJumped() override;

  protected:
    /* Protected functions*/
   /* void LogMove(float DeltaTime) override;*/

    void BeaverLogScore() override;
};
