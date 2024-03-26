// Fill out your copyright notice in the Description page of Project Settings.

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
	//virtual void Tick(float DeltaTime) override;

	public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    class UBoxComponent *triggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
     float customBlendTime;

	UPROPERTY()
    FName gameLevel;

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float timeBeforeStartGame;

    UPROPERTY()
    FName menuLevel;

    UPROPERTY()
    APlayerController *playerController=nullptr;

    UPROPERTY(EditAnywhere)
    AActor *cameraPlayerMenu;

    UPROPERTY(EditAnywhere)
    AActor *cameraPlayerInGame;

    void StartTimerBeforeGameStarts();
    void ChangeCurrentLevel(const FName &levelName);

    UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32
                        OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32
                      OtherBodyIndex);
};
