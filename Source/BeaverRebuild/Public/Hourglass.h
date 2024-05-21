// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hourglass.generated.h"

USTRUCT(BlueprintType)
struct FHourglassParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float SlowdownScale = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LifeTime = 15;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 timeForSlow = 9;
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
    FHourglassParameters HourParams;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent* SphereComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* StaticMesh;

  private:
    /*Private variables*/
    bool bItemPicked = true;

    UPROPERTY()
    class APlayerBeaver* PlayerBeaver = nullptr;

    /* Private functions*/
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);

    void ReturnToDefault();
    void SlowdownLogs();
};
