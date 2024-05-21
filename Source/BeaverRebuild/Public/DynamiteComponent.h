// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DynamiteComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BEAVERREBUILD_API UDynamiteComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UDynamiteComponent();

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class ADynamite> DynamiteClass;

  public:
    void SpawnDynamite(class ABeaverLog* Log);
};
