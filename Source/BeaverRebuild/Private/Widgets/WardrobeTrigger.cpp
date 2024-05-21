// Copyright (c) 2024 Allure Games.

#include "Widgets/WardrobeTrigger.h"
#include "Components/BoxComponent.h"
#include "PlayerBeaver.h"
#include "BeaverGameInstance.h"
#include "BeaverPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverGameMode.h"
#include "Runtime/Engine/Classes/Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AWardrobeTrigger::AWardrobeTrigger()
{
    PrimaryActorTick.bCanEverTick          = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    TriggerBox                             = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
    TimeLineComponent                      = CreateDefaultSubobject<UTimelineComponent>(TEXT("Time Line"));

    SetRootComponent(TriggerBox);
}

void AWardrobeTrigger::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWardrobeTrigger::OnOverlapBegin);

    Beaver           = StaticCast<APlayerBeaver*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    GameMode         = StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode());
    PlayerController = StaticCast<ABeaverPlayerController*>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    GameMode->WardrobeTrigger = this;
    GameMode->OnBackToGame.AddUObject(this, &AWardrobeTrigger::OnReturnPlayerToGame);

    if (CurveFloat)
    {
        FOnTimelineFloat FunctionFloatDelegate;

        FunctionFloatDelegate.BindDynamic(this, &AWardrobeTrigger::UpdateTimelineComp);

        TimeLineComponent->AddInterpFloat(CurveFloat, FunctionFloatDelegate);
    }
}

void AWardrobeTrigger::UpdateTimelineComp(float Alpha)
{
    float BeaverVelocity                       = FMath::Lerp(BeaverVelocityMax, BeaverVelocityMin, Alpha);
    Beaver->GetCharacterMovement()->Velocity.Y = bIsInWardrobe ? -BeaverVelocity : (BeaverVelocity + 100);

    if (!TimeLineComponent->IsPlaying())
    {
        bIsInWardrobe ? GameMode->SetGameState(EBeaverGameState::WardrobeMenu)
                      : (TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly), Beaver->EnableInput(PlayerController.Get()));

        Beaver->SetActorRelativeRotation(FRotator{0, 0, 0});
    }
}

void AWardrobeTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!GetWorld()->GetAuthGameMode() || !Beaver.IsValid())
    {
        return;
    }

    bIsInWardrobe = true;

    Beaver->DisableInput(PlayerController.Get());
    Beaver->GetCharacterMovement()->Velocity = FVector::ZeroVector;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    PlayWardrobeTransition();
}

void AWardrobeTrigger::OnReturnPlayerToGame()
{
    if (!GetWorld()->GetAuthGameMode() || !Beaver.IsValid())
    {
        return;
    }

    bIsInWardrobe = false;

    Beaver->SetActorRelativeRotation(FRotator{0, 90, 0});

    GameMode->SetGameState(EBeaverGameState::InProgress);

    PlayWardrobeTransition();
}

void AWardrobeTrigger::PlayWardrobeTransition()
{
    if (!PlayerController.IsValid())
    {
        return;
    }

    FViewTargetTransitionParams TransitionParams;

    TransitionParams.BlendTime = CustomBlendTime;

    bIsInWardrobe ? TimeLineComponent->Play() : TimeLineComponent->Reverse();

    PlayerController->SetViewTarget(bIsInWardrobe ? CameraPlayerWardrobe : CameraPlayerInGame, TransitionParams);
}