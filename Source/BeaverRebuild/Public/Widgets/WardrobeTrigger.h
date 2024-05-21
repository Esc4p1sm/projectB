// Copyright (c) 2024 Allure Games.

#pragma once
#include "Libs/BeaverTypes.h"
#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WardrobeTrigger.generated.h"

UCLASS()
class BEAVERREBUILD_API AWardrobeTrigger : public AActor
{
    GENERATED_BODY()

  public:
    AWardrobeTrigger();

  protected:
    virtual void BeginPlay() override;

  public:
    UPROPERTY(EditAnywhere)
    float CustomBlendTime = 3.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere)
    AActor* CameraPlayerWardrobe = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* CameraPlayerInGame = nullptr;

    UPROPERTY(EditAnywhere)
    UCurveFloat* CurveFloat = nullptr;

    bool bIsInWardrobe = false;

    void OnReturnPlayerToGame();

  private:
    const float BeaverVelocityMin = 550.f;
    const float BeaverVelocityMax = 600.f;

    TWeakObjectPtr<class APlayerBeaver> Beaver;

    TWeakObjectPtr<class ABeaverGameMode> GameMode;

    TWeakObjectPtr<class ABeaverPlayerController> PlayerController;

    UPROPERTY()
    UTimelineComponent* TimeLineComponent;

    UFUNCTION()
    void UpdateTimelineComp(float Alpha);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);

    void PlayWardrobeTransition();
};
