// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BeaverLog.h"
#include "PlayerBeaver.h"
#include "Misc/FileHelper.h"
#include "Misc/DateTime.h"

#include "AchivementManager.generated.h"

/**
 * 
 */
UENUM()
enum EAchivementType
{
    LogTypeAchive,
    BeaverTypeAchive,
    SkinTypeAchive,
    EnvironmentTypeAchive
};

UENUM()
enum EBeaverAchivementType
{
    RunType,
    JumpType,
    DoubleJumpType,
    ClimbType,
    FlyType,
    FastLandType
};

UENUM()
enum ESkinAchivementType
{
    HatTypeAchive    = 1,
    BodyTypeAchive = 2,
    LevelTypeAchive  = 4,
    ChinaTypeAchive  = 8,
    SpaceTypeAchive  = 16,
    DesertTypeAchive = 32,
    CreepyTypeAchive = 64,
    GoldTypeAchive   = 128
};

UENUM()
enum ELogAchivementType
{
    StandardLogType,
    SwampLogType,
    HugeLogType,
    ShieldLogType,
    GoldLogType,
    LogOfTimeType,
    TotalLogType
};

UENUM()
enum EEnvironmentAchivementType
{
    ShieldType,
    TimeType,
    DeflectType
};

UENUM()
enum EnvironmentEvent
{
    ShieldBeging,
    ShieldEnd,
    TimeSlowed,
    TimeRestored,
    LogDeflected
};

USTRUCT(BlueprintType)
struct FLogStatistic
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    int32 totalLogsJumped = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    int32 standardLogsJumped = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    int32 giantLogsJumped = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    int32 goldLogsJumped = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    int32 clockLogsJumped = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    int32 spoiledLogsJumped = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    int32 tarLogsJumped = 0;
};

USTRUCT(BlueprintType)
struct FBeaverStatistic
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    int32 jumpsMade = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    int32 doubleJumpsMade = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    int32 wallLaunched = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    int32 maxDives = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    float maxOnGroundTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    float maxOnWallTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    float maxInAirTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    float totalOnGroundTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    float totalOnWallTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    float totalInAirTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FEnvironmentStatistics
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    float maxSlowedTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    float maxShieldTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    float totalSlowedTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    float totalShieldTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    float curSlowedTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    float curShieldTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    int32 hourglassesCollected = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    int32 shieldsCollected = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    int32 logsDeflected = 0;
};

USTRUCT(BlueprintType)
struct FBaseAchivement
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    TEnumAsByte<EAchivementType> achivementType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    FString achivementName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    bool bIsGlobal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    bool isRound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    bool isCompleted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    bool isNeedGreater;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    int32 reward;
};

USTRUCT(BlueprintType)
struct FBeaverAchivement : public FBaseAchivement
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    bool isCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    float targetAmmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    TEnumAsByte<EBeaverAchivementType> type;
};

USTRUCT(BlueprintType)
struct FLogAchivement : public FBaseAchivement
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    TEnumAsByte<ELogAchivementType> type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    int32 count;
};

USTRUCT(BlueprintType)
struct FEnvironmentAvhivement : public FBaseAchivement
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    TEnumAsByte<EEnvironmentAchivementType> type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    bool isCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    float targetAmount;
};

USTRUCT(BlueprintType)
struct FSkinAchivement : public FBaseAchivement
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achevement info")
    uint8 type;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAchivementReachedDelegate, FBaseAchivement, achivement);

/**
 *
 */
UCLASS()
class BEAVERREBUILD_API UAchivementManager : public UObject
{
    GENERATED_BODY()

  public:
    UAchivementManager(const FObjectInitializer &ObjectInitializer);

    UFUNCTION()
    void setSkins(uint8 hat, uint8 body, uint8 level);

    UFUNCTION()
    void setWorld(UWorld *gameWorld);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FBeaverAchivement> beaverAchivements;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FLogAchivement> logAchivements;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FEnvironmentAvhivement> environmentAchivements;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FSkinAchivement> skinAchivements;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log statistic")
    FLogStatistic logStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beaver statistic")
    FBeaverStatistic beaverStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment statistic")
    FEnvironmentStatistics envStats;

    UFUNCTION()
    void CountLogStats(TEnumAsByte<ELogType> LogType);

    UFUNCTION(BlueprintCallable)
    void ClearStatistic();

    UFUNCTION()
    void CountBeaverStats(BeaverState newState);

    UFUNCTION()
    void CountEnvironmentEvent(EnvironmentEvent event);

    UFUNCTION(BlueprintCallable)
    void CheckTimers();

    UFUNCTION()
    void CheckAchivements(EAchivementType achivementType);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FBeaverStatistic globBeaverStats;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FLogStatistic globLogStats;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FEnvironmentStatistics globEnvStats;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FAchivementReachedDelegate onAchivementReached;

    UFUNCTION()
    void CheckBeaver();
    UFUNCTION()
    void CheckLogs();
    UFUNCTION()
    void CheckEnvironment();
    UFUNCTION()
    void CheckSkins();

    UFUNCTION()
    void saveStatistic();
    void addSaveString();
    void addFinalString();

    void startCountStat();

    UPROPERTY()
    UWorld *world;

    int32 inGameMins = 0;
    FString statString;

    FTimerHandle onGroundTimer;
    FTimerHandle onWallTimer;
    FTimerHandle inAirTimer;
    FTimerHandle afterFastLandTimer;
    FTimerHandle shieldTimer;
    FTimerHandle slowedTimer;
    FTimerHandle gameTimer;

  private:
    uint8 hatSkins, bodySkins, levelSkins;

    float currShieldTime  = 0.0f;
    float currSlowTime    = 0.0f;
    float curOnGroundTime = 0.0f;
    float curOnWallTime   = 0.0f;
    float curInAirTime    = 0.0f;
};
