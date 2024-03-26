// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hourglass.generated.h"



USTRUCT(BlueprintType)
struct FHourglassParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float slowdownScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 lifeTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 timeForSlow;
};

UCLASS()
class BEAVERREBUILD_API AHourglass : public AActor
{
    GENERATED_BODY()

  public:
    AHourglass();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hourglass Parameters")
    FHourglassParameters hourParams;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent *sphereComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent *staticMesh;

  private:
    /*Private variables*/
    UPROPERTY()
    bool bItemPicked;

    UPROPERTY()
    class APlayerBeaver *ptrBeaver;
  
    /* Private functions*/
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
   
    void ReturnToDefault();
    void SlowdownLogs();
};
