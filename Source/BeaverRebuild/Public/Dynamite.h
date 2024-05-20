// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dynamite.generated.h"

UCLASS()
class BEAVERREBUILD_API ADynamite : public AActor
{
    GENERATED_BODY()

  public:
    ADynamite();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    class ABeaverLog* FollowLog = nullptr;

  protected:
    UPROPERTY(EditDefaultsOnly)
    float FollowingSpeed = 1;

    UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* StaticMeshComponent;

  private:
    UPROPERTY(EditAnywhere)
    UCurveFloat* CurveFloat = nullptr;

    UPROPERTY()
    UTimelineComponent* TimeLineComponent;

    FVector CurrentDynamiteLocation;

    UFUNCTION()
    void UpdateTimelineComp(float Alpha);
};
