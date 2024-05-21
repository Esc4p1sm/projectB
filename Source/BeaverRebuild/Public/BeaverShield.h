// Copyright (c) 2024 Allure Games.

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
    int32 LifeTime = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of Shield")
    float Speedup = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent* SphereComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMeshComponent* StaticMesh;

  private:
    /*Private variables*/
    UPROPERTY()
    class APlayerBeaver* PlayerBeaver = nullptr;

    /* Private functions*/
    UFUNCTION()
    void OnOverlapShieldBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                              const FHitResult& Hit);

    void DestroyPickedShield();
    void ChangeShieldComponentsParams();
    void ChangeBeaverCapsuleCollision(const ECollisionResponse Response);
};
