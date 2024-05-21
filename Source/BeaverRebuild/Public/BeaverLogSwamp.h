// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "BeaverLog.h"
#include "BeaverLogSwamp.generated.h"

UCLASS()
class BEAVERREBUILD_API ABeaverLogSwamp : public ABeaverLog
{
    GENERATED_BODY()

  public:
    ABeaverLogSwamp();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SwampAdditionalTime = 5.f;

    UFUNCTION()
    void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                        const FHitResult& Hit);
};
