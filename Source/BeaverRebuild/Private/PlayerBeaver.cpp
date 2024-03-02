// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBeaver.h"
#include "BeaverGameMode.h"
#include "BeaverLog.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LogSpawner.h"

// Sets default values
APlayerBeaver::APlayerBeaver()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick       = true;
    bOnWall                             = false;
    bWasOnGround                        = true;
    BeaverParams.beaverLocationForSpawn = FVector{50.0f, 0.0f, 10.0f};
    BeaverParams.traceMaxDistance       = 150.f;
    BeaverParams.slidingSpeed           = -20.f;
    BeaverParams.forceJumpScale         = 700;
    BeaverParams.forceDownScale         = 1000;
    jumpCount                           = 0;
}

void APlayerBeaver::BeginPlay()
{
    Super::BeginPlay();
    
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerBeaver::OnOverlapBegin);
    GetCapsuleComponent()->SetGenerateOverlapEvents(true);
   
    SetActorRotation(FRotator::ZeroRotator);

    Cast<ABeaverGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddBeaver(this);

    FTimerHandle timerHandleClimbing;
    GetWorldTimerManager().SetTimer(timerHandleClimbing, this, &APlayerBeaver::Climbing, 0.1f, true);
   
}

void APlayerBeaver::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MarkJumpedLogs();
}

// Called to bind functionality to input
void APlayerBeaver::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveRight", this, &APlayerBeaver::OnMoveRight);
    InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerBeaver::OnStartJump);
    InputComponent->BindAction("Jump", IE_Released, this, &APlayerBeaver::OnStopJump);
    InputComponent->BindAction("ForceJump", IE_Pressed, this, &APlayerBeaver::OnForceWallJump);
    InputComponent->BindAction("ForceDown", IE_Pressed, this, &APlayerBeaver::OnForceMoveDown);
}

void APlayerBeaver::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
                                   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult &SweepResult)
{
    ABeaverLog *beaverLog = Cast<ABeaverLog>(OtherActor);

    if (IsValid(beaverLog) && OtherComp)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Beaver overlaped"));
        Cast<ABeaverGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->FinishRound();
        Destroy();
    }
}

void APlayerBeaver::MarkJumpedLogs()
{
    const FVector traceStart = GetActorLocation();
   const FVector traceEnd   = FVector(traceStart.X, traceStart.Y, 0.0f);
    FHitResult hitResult;

    DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Red, false, 0, 0, 3);
    
    GetWorld()->LineTraceSingleByChannel(hitResult, traceStart, traceEnd, ECollisionChannel::ECC_GameTraceChannel1);
    if (hitResult.bBlockingHit)
    {
        if (Cast<ABeaverLog>(hitResult.GetActor()))
        {
            Cast<ABeaverLog>(hitResult.GetActor())->MarkAsJumped();
        }
    }
}

void APlayerBeaver::Climbing()
{
    if (GetCharacterMovement()->IsFalling())
    {
        const FVector traceStart     = GetActorLocation();
        const FVector traceEnd = traceStart + 45 * GetActorForwardVector();
        GetWorld()->LineTraceSingleByChannel(hitResultClimbing, traceStart, traceEnd,
                                             ECollisionChannel::ECC_GameTraceChannel2);
        DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Green, false, 0, 0, 3);

        if (hitResultClimbing.bBlockingHit && bWasOnGround)
        {
            bOnWall                              = true;
            bWasOnGround                         = false;
            GetCharacterMovement()->GravityScale = 0;
            GetCharacterMovement()->Velocity.Z   = BeaverParams.slidingSpeed;
            jumpCount                            = JumpCurrentCount;
        }
        else if (!hitResultClimbing.bBlockingHit && bOnWall)
        {
            GetCharacterMovement()->GravityScale = 1;
            bOnWall                              = false;

            if (jumpCount == 1) JumpCurrentCount = 0; 
        }
    }
}

void APlayerBeaver::OnForceWallJump()
{
    if (bOnWall)
    {
        const FVector launchDirection = {0, -GetActorForwardVector().Y, 1};
        const FRotator launchRotation = {0, -GetActorRotation().Yaw, 0};

        LaunchCharacter(launchDirection * BeaverParams.forceJumpScale, true, true);
        SetActorRotation(launchRotation);
    }
}

void APlayerBeaver::OnForceMoveDown()
{
    if (GetCharacterMovement()->IsFalling() && !bOnWall)
    {
        LaunchCharacter(-GetActorUpVector() * BeaverParams.forceDownScale, false, false);
    }
}

void APlayerBeaver::Landed(const FHitResult &Hit)
{
    Super::Landed(Hit);

    bWasOnGround = true;
    jumpCount    = 0;
}
