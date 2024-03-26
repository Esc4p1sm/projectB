// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent *triggerSphere;

    

    UPROPERTY(EditAnywhere)
    AActor *cameraPlayerWardrobe;

    UPROPERTY()
    UTimelineComponent *timelineComp;

    UPROPERTY(EditAnywhere)
    UCurveFloat *curveFloat;

    FOnTimelineFloat UpdateFunctionFloat;

    class APlayerBeaver* beaver;

    UFUNCTION()
    void UpdateTimelineComp(float alpha);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult &SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, 
                      int32 OtherBodyIndex);
};
