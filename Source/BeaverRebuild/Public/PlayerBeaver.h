// Copyright (c) 2024 Allure Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBeaver.generated.h"

UENUM(BlueprintType)
enum BeaverState
{
    isUndefined     = 0,
    isJumped        = 1,
    isLanded        = 2,
    isClimbing      = 4,
    isLaunched      = 8,
    isFastLanding   = 16,
    isDoubleJumping = 32
};

USTRUCT(BlueprintType)
struct FBeaverParameters : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SlidingSpeed = -20.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 150.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ForceJumpScale = 700;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ForceDownScale = 1000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector BeaverLocationForSpawn = FVector{50.0f, 0.0f, 10.0f};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeaverStateDelegate, BeaverState, state);

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

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /* Public variables*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters of Beaver")
    FBeaverParameters BeaverParams;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* HatMesh;

    /* Public functions*/
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Beaver")
    FBeaverStateDelegate OnBeaverStateChanged;

    uint8 BeaverState = 0;

    UPROPERTY(BlueprintReadOnly)
    bool bOnWall = false;

    UPROPERTY(EditAnywhere)
    UAnimMontage* TouchdownAnimMontage;

    UPROPERTY(EditAnywhere)
    UAnimMontage* JumpFromWallAnimMontage;

    /* Public functions*/
    void SetBeaverHat(UStaticMesh* const StaticMesh);
    void SetBeaverSkin(USkeletalMesh* const SkeletalMesh);

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Sounds")
    class USoundCue* JumpSound;

    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Sounds")
    USoundCue* ReboundSound;

    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Sounds")
    USoundCue* FallSound;

    UPROPERTY(EditDefaultsOnly)
    class UDynamiteComponent* DynamiteComponent;

  private:
    /* Private variables*/
    bool isJumped       = false;
    bool isDoubleJumped = false;
    bool isDived        = false;
    bool bWasOnGround   = true;

    FHitResult HitResultClimbing;

    int32 JumpCount = 0;

    /* Private functions*/
    UFUNCTION()
    void MarkJumpedLogs();

    UFUNCTION()
    void Climbing();

    void Landed(const FHitResult& Hit) override;

    /*Action inputs*/
    void OnForceMoveDown();
    void OnForceWallJump();
    void OnMoveRight(float Value);
    void OnStartJump();
    void OnStopJump();
};
