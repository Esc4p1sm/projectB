// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/WardrobeTrigger.h"
#include "Components/SphereComponent.h"
#include "PlayerBeaver.h"
#include "BeaverPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverGameMode.h"

#include "Runtime/Engine/Classes/Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"

AWardrobeTrigger::AWardrobeTrigger()
{
    PrimaryActorTick.bCanEverTick          = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    bIsInWardrobe                          = false;
    triggerSphere                          = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
    timeLineComponent                      = CreateDefaultSubobject<UTimelineComponent>(TEXT("Time Line"));
    customBlendTime                        = 3;

    SetRootComponent(triggerSphere);
}

void AWardrobeTrigger::BeginPlay()
{
    Super::BeginPlay();

    triggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AWardrobeTrigger::OnOverlapBegin);

    beaver = Cast<APlayerBeaver>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    Cast<ABeaverGameMode>(GetWorld()->GetAuthGameMode())->onGameStateChange.AddUObject(this, &AWardrobeTrigger::OnReturnPlayerToGame);
    if (curveFloat)
    {
        FOnTimelineFloat functionFloatDelegate;

        functionFloatDelegate.BindDynamic(this, &AWardrobeTrigger::UpdateTimelineComp);

        

        timeLineComponent->AddInterpFloat(curveFloat, functionFloatDelegate);
    }
}

void AWardrobeTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWardrobeTrigger::UpdateTimelineComp(float alpha)
{
    FVector currentPlayerLocation = beaver->GetActorLocation();
    float delataAlpha             = FApp::GetDeltaTime() * (bIsInWardrobe ? alpha : -alpha);
    FVector playerNewLocation     = FVector{currentPlayerLocation.X, currentPlayerLocation.Y - delataAlpha, currentPlayerLocation.Z};

    beaver->SetActorRelativeLocation(playerNewLocation);

    if (!timeLineComponent->IsPlaying())
    {
        
            Cast<ABeaverGameMode>(GetWorld()->GetAuthGameMode())->SetGameState(EBeaverGameState::WardrobeMenu);
        

        beaver->SetActorRelativeRotation(FRotator{0, 0, 0});
    }
}

void AWardrobeTrigger::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode() || !beaver.IsValid())
        return;

    FViewTargetTransitionParams params;
    params.BlendTime      = customBlendTime;
    auto playerController = Cast<ABeaverPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    if (IsValid(playerController))
    {
        timeLineComponent->Play();

        playerController->SetViewTarget(cameraPlayerWardrobe, params);
        playerController->ChangeMenuNavigation();

        beaver->DisableInput(playerController);
        beaver->GetCharacterMovement()->Velocity = FVector::ZeroVector;
        bIsInWardrobe                            = true;
    }
}

void AWardrobeTrigger::OnReturnPlayerToGame(EBeaverGameState state)
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode() || !beaver.IsValid())
        return;

    if (state==EBeaverGameState::InProgress && bIsInWardrobe)
    {
        FViewTargetTransitionParams params;
        params.BlendTime      = customBlendTime;
        auto playerController = Cast<ABeaverPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

        if (IsValid(playerController))
        {
            timeLineComponent->Reverse();

            playerController->SetViewTarget(cameraPlayerInGame, params);

            beaver->EnableInput(playerController);
            bIsInWardrobe = false;
        }
    }
}
