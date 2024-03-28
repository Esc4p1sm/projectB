// Fill out your copyright notice in the Description page of Project Settings.

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
    // Sets default values for this actor's properties
    AWardrobeTrigger();

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

  public:
    UPROPERTY(EditAnywhere)
    float customBlendTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent *triggerSphere;

    UPROPERTY(EditAnywhere)
    AActor *cameraPlayerWardrobe = nullptr;

    UPROPERTY(EditAnywhere)
    AActor *cameraPlayerInGame = nullptr;

    UPROPERTY(EditAnywhere)
    UCurveFloat *curveFloat = nullptr;

    bool bIsInWardrobe;
    
    void OnReturnPlayerToGame(EBeaverGameState state);
  private:
    TWeakObjectPtr<class APlayerBeaver> beaver;
    
    UPROPERTY()
    UTimelineComponent *timeLineComponent;

    UFUNCTION()
    void UpdateTimelineComp(float alpha);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult &SweepResult);
    
};
