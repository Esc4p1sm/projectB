// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerBeaver.h"
#include "CoreMinimal.h"
#include "LogSpawner.h"
#include "Libs/BeaverTypes.h"
#include "GameFramework/GameMode.h"
#include "BeaverGameMode.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeLeftDelegate, int32, timeLeft);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreDelegate, int32, score);

UCLASS()
class BEAVERREBUILD_API ABeaverGameMode : public AGameMode
{
    GENERATED_BODY()

  public:
    ABeaverGameMode();

    virtual void DecreaseLifeTime();

    virtual void AddScore(int32 ScoreAmount);

    void AddBeaver(class APlayerBeaver* Beaver);

    void StartPlay() override;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void FinishRound();

    UFUNCTION(BlueprintCallable)
    virtual void AddLifeTime(int32 AdditionalTime);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player info")
    int32 BeaverScore = 0;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    FTimerHandle LifeTimerHandle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player info")
    int32 BeaverLifeTime = 40;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner info")
    ALogSpawner* LogSpawner;

    UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "Delegates")
    FTimeLeftDelegate OnLifeTimerUpdated;

    UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "Delegates")
    FScoreDelegate OnScoreUpdated;

    FOnGameStateChangeSignature OnGameStateChange;

    FOnBackToGameSignature OnBackToGame;

    EBeaverGameState GameState = EBeaverGameState::Waiting;

    void StartGame();
    void SetGameState(EBeaverGameState State);

    TWeakObjectPtr<class AWardrobeTrigger> WardrobeTrigger;

    UPROPERTY()
    class UAudioComponent* AudioComponent;

    UPROPERTY(EditDefaultsOnly)
    class USoundCue* MenuSoundCue;

    void SetCurrentGameMusic(USoundCue* SoundCue);

  protected:
    virtual void BeginPlay() override;
    bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    bool ClearPause() override;

    UPROPERTY()
    APlayerBeaver* BeaverPawn;
};
