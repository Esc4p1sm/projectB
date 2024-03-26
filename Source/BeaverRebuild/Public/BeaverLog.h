// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeaverLog.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishRound);

USTRUCT(BlueprintType)
struct FLogParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float scaleSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 lifeTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 impactCounterMax;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 additionalSlivers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 additionalTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 additionalScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float timeToDestruction;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector logDirection;
};
 
UCLASS()
class BEAVERREBUILD_API ABeaverLog : public AActor
{
    GENERATED_BODY()

  public:
    ABeaverLog();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of the Log")
    FLogParameters logParams;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent *boxComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsJumped;

    UPROPERTY()
    FOnFinishRound onFinishRound;

    static float customSpeedScale;

    /* Public functions*/
    UFUNCTION()
    virtual void MarkAsJumped();

  protected:
    /* Protected variables*/
    UPROPERTY()
    FVector reflectionVector;

    UPROPERTY()
    FTimerHandle timerHandle;

    UPROPERTY()
    FHitResult hitResult;

    /* Protected functions*/
    UFUNCTION()
    virtual void LogMove(float DeltaTime);

    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

    UFUNCTION()
    virtual void BeaverLogScore();

    virtual void BeaverLogSlivers();

};
