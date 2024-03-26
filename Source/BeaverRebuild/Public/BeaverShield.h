// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeaverShield.generated.h"


UCLASS()
class BEAVERREBUILD_API ABeaverShield : public AActor
{
    GENERATED_BODY()

  public:
    ABeaverShield();

  protected:
    virtual void BeginPlay() override;

  public:
    void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of Shield")
    int32 lifeTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of Shield")
    float speedup;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent *sphereComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMeshComponent *staticMesh;

  private:
    /*Private variables*/
    UPROPERTY()
    class APlayerBeaver *ptrBeaver;

    /* Private functions*/
    UFUNCTION()
    void OnOverlapShieldBegin(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                              FVector NormalImpulse, const FHitResult &Hit);

    void DestroyPickedShield();
    void ChangeShieldComponentsParams();
    void ChangeBeaverCapsuleCollision(const ECollisionResponse response);
};
