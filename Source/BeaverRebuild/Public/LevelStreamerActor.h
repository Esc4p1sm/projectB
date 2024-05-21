// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamerActor.generated.h"

UCLASS()
class BEAVERREBUILD_API ALevelStreamerActor : public AActor
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    ALevelStreamerActor();

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    // virtual void Tick(float DeltaTime) override;

  public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CustomBlendTime = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeBeforeStartGame = 5.f;

    UPROPERTY()
    FName MenuLevel = "MenuLevel";

    UPROPERTY()
    APlayerController* PlayerController = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* CameraPlayerMenu;

    UPROPERTY(EditAnywhere)
    AActor* CameraPlayerInGame;

    UPROPERTY(EditDefaultsOnly)
    TMap<FName, class USoundCue*> GameSound;

    TWeakObjectPtr<class UBeaverGameInstance> GameInstance;

    void StartTimerBeforeGameStarts();
    void ChangeCurrentLevel(const FName& LevelName);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
