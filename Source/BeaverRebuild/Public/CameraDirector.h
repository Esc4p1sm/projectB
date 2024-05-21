// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class BEAVERREBUILD_API ACameraDirector : public AActor
{
    GENERATED_BODY()

  public:
    
    ACameraDirector();

  protected:
    
    virtual void BeginPlay() override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere)
    AActor *cameraPlayer;
};
