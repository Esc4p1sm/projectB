// Copyright (c) 2024 Allure Games.

#include "PlayerBeaver.h"
#include "BeaverGameInstance.h"
#include "BeaverGameMode.h"
#include "BeaverLog.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LogSpawner.h"
#include "BeaverPlayerController.h"
#include "libs/BeaverTypes.h"
#include "Sound/SoundCue.h"
#include "DynamiteComponent.h"

APlayerBeaver::APlayerBeaver()
{
    PrimaryActorTick.bCanEverTick = true;
    HatMesh                       = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat Mesh"));
    DynamiteComponent             = CreateDefaultSubobject<UDynamiteComponent>(TEXT("Dynamite Component"));
}

void APlayerBeaver::BeginPlay()
{
    Super::BeginPlay();

    GetCapsuleComponent()->SetGenerateOverlapEvents(true);

    SetActorRotation(FRotator::ZeroRotator);

    const auto GameMode = StaticCast<ABeaverGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));

    if (GameMode)
    {
        GameMode->AddBeaver(this);
    }

    FTimerHandle TimerHandleClimbing;
    GetWorldTimerManager().SetTimer(TimerHandleClimbing, this, &APlayerBeaver::Climbing, 0.1f, true);

    const auto GameInstance = StaticCast<UBeaverGameInstance*>(GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        GameInstance->linkBeaver(this);
    }
}

void APlayerBeaver::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    MarkJumpedLogs();
}

void APlayerBeaver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerBeaver::OnMoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerBeaver::OnStartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerBeaver::OnStopJump);
    PlayerInputComponent->BindAction("ForceJump", IE_Pressed, this, &APlayerBeaver::OnForceWallJump);
    PlayerInputComponent->BindAction("ForceDown", IE_Pressed, this, &APlayerBeaver::OnForceMoveDown);
}

void APlayerBeaver::MarkJumpedLogs()
{
    const FVector TraceStart = GetActorLocation();
    const FVector TraceEnd   = FVector(TraceStart.X, TraceStart.Y, 0.0f);

    TArray<FHitResult> HitResults;

    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0, 0, 3);

    GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, TraceEnd, ECollisionChannel::ECC_MARK_LOGS_TRACE_CHANNEL);

    for (FHitResult& HitResult : HitResults)
    {
        const auto Log = Cast<ABeaverLog>(HitResult.GetActor());

        if (IsValid(Log))
        {
            if (!Log->bIsJumped)
            {
                DynamiteComponent->SpawnDynamite(Log);
            }

            Log->MarkAsJumped();
        }
    }
}

void APlayerBeaver::Climbing()
{
    if (GetCharacterMovement()->IsFalling()) //(beaverState & BeaverState::isJumped)//
    {
        const FVector TraceStart = GetActorLocation();
        const FVector TraceEnd   = TraceStart + 45 * GetActorForwardVector();

        GetWorld()->LineTraceSingleByChannel(HitResultClimbing, TraceStart, TraceEnd, ECollisionChannel::ECC_CLIMBING_TRACE_CHANEL);
        DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 0, 0, 3);

        if (HitResultClimbing.bBlockingHit && bWasOnGround)
        {
            bOnWall                              = true;
            bWasOnGround                         = false;
            BeaverState                          = BeaverState::isClimbing;
            GetCharacterMovement()->GravityScale = 0;
            GetCharacterMovement()->Velocity.Z   = BeaverParams.SlidingSpeed;
            JumpCount                            = JumpCurrentCount;

            OnBeaverStateChanged.Broadcast(BeaverState::isClimbing);
        }
        else if (!HitResultClimbing.bBlockingHit && bOnWall) //(beaverState & BeaverState::isJumped)
        {
            GetCharacterMovement()->GravityScale = 1;
            bOnWall                              = false;

            OnBeaverStateChanged.Broadcast(BeaverState::isJumped);

            if (JumpCount == 1)
            {
                JumpCurrentCount = 0;
            }
        }
    }
}

void APlayerBeaver::OnForceWallJump()
{
    if (bOnWall)
    {
        const FVector LaunchDirection = {0, -GetActorForwardVector().Y, 1};
        const FRotator LaunchRotation = {0, -GetActorRotation().Yaw, 0};

        if (JumpFromWallAnimMontage)
        {
            PlayAnimMontage(JumpFromWallAnimMontage);
        }

        if (ReboundSound)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReboundSound, GetActorLocation());
        }

        LaunchCharacter(LaunchDirection * BeaverParams.ForceJumpScale, true, true);

        SetActorRotation(LaunchRotation);

        OnBeaverStateChanged.Broadcast(BeaverState::isLaunched);
    }
}

void APlayerBeaver::OnForceMoveDown()
{
    if (GetCharacterMovement()->IsFalling() && !bOnWall)
    {
        PlayAnimMontage(TouchdownAnimMontage);

        LaunchCharacter(-GetActorUpVector() * BeaverParams.ForceDownScale, false, false);
        OnBeaverStateChanged.Broadcast(BeaverState::isFastLanding);
    }
}

void APlayerBeaver::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    if (FallSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), FallSound, GetActorLocation());
    }

    bWasOnGround = true;
    JumpCount    = 0;
    OnBeaverStateChanged.Broadcast(BeaverState::isLanded);
}

void APlayerBeaver::OnMoveRight(float Value)
{
    AddMovementInput(GetOwner()->GetActorRightVector(), Value);
}

void APlayerBeaver::OnStartJump()
{
    if (JumpSound && !bOnWall && !GetCharacterMovement()->IsFalling())
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpSound, GetActorLocation());
    }

    bPressedJump = true;
}

void APlayerBeaver::OnStopJump()
{
    bPressedJump = false;
}

void APlayerBeaver::SetBeaverHat(UStaticMesh* const StaticMesh)
{
    if (StaticMesh)
    {
        FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);

        HatMesh->SetStaticMesh(StaticMesh);
        HatMesh->RegisterComponent();
        HatMesh->AttachToComponent(GetMesh(), AttachmentTransformRules, "HatSocket");
    }
}

void APlayerBeaver::SetBeaverSkin(USkeletalMesh* const SkeletalMesh)
{
    if (SkeletalMesh)
    {
        GetMesh()->SetSkeletalMesh(SkeletalMesh);
    }
}