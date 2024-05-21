// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/EnumAsByte.h"
#include "BeaverLog.generated.h"

UENUM(BlueprintType)
enum ELogType
{
    StandardLog,
    SwampLog,
    ClockedLog,
    GoldLog,
    TarLog,
    HugeLog
};

USTRUCT(BlueprintType)
struct FLogParameters : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float Speed = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ScaleSpeed = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AngleRotation = 60;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LifeTime = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ImpactCounterMax = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AdditionalSlivers = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AdditionalTime = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AdditionalScore = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeToDestruction = 2.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector LogDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of Log")
    TEnumAsByte<ELogType> TypeOfLog;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLogTypeDelegate, TEnumAsByte<ELogType>, TypeOfLog);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLogRefDelegate, ABeaverLog*, Log);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishRound);

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
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void PostInitProperties() override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of the Log")
    FLogParameters LogParams;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UCapsuleComponent* CapsuleComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsJumped;

    FOnFinishRound OnFinishRound;

    static float CustomSpeedScale;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Test")
    FLogTypeDelegate OnLogScored;

    /* Public functions*/
    UFUNCTION()
    virtual void MarkAsJumped();

  protected:
    /* Protected variables*/

    FVector ReflectionVector;

    FTimerHandle TimerHandle;

    FHitResult HitResult;

    FTimerHandle TimerToDestroy;

    UPROPERTY(EditDefaultsOnly)
    class USoundCue* ImpactSound = nullptr;

    UPROPERTY()
    TArray<UStaticMeshComponent*> LogComponents;

    /* Protected functions*/
    UFUNCTION()
    virtual void LogMove(float DeltaTime);

    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void BeaverLogScore();

    virtual void LogRotation(float DeltaTime);
    virtual void BeaverLogSlivers();

    void GraduallyDestroyBark();
    void DestroyCoreLog();
    void DestroyLogByTime();
    void FillArrayByComponents();
};
