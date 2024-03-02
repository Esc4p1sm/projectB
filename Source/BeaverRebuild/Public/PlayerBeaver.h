// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBeaver.generated.h"


USTRUCT(BlueprintType)
struct FBeaverParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float slidingSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float traceMaxDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 forceJumpScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 forceDownScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector beaverLocationForSpawn;
};

UCLASS()
class BEAVERREBUILD_API APlayerBeaver : public ACharacter
{
    GENERATED_BODY()

  public:
    APlayerBeaver();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

  public:
    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of Beaver")
    FBeaverParameters BeaverParams;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent *componentShield;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMeshComponent *meshShield;

  private:
    /* Private variables*/
    UPROPERTY()
    bool bOnWall;

    UPROPERTY()
    bool bWasOnGround;

    UPROPERTY()
    FHitResult hitResultClimbing;

    UPROPERTY()
    int32 jumpCount;

    /* Private functions*/
    UFUNCTION()
    void MarkJumpedLogs();

    UFUNCTION()
    void Climbing();

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

    void Landed(const FHitResult &Hit) override;

    /*Action inputs*/    
    void OnForceMoveDown();
    void OnForceWallJump();

    void OnMoveRight(float value) { AddMovementInput(GetOwner()->GetActorRightVector(), value); }

    void OnStartJump() { bPressedJump = true; }

    void OnStopJump() { bPressedJump = false; }
};
