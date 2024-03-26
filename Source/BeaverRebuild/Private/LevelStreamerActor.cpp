// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelStreamerActor.h"
#include "Components/BoxComponent.h"
#include "PlayerBeaver.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelStreamerActor::ALevelStreamerActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    gameLevel       = "GameLevel";
    menuLevel       = "MenuLevel";
    customBlendTime = 1;
    timeBeforeStartGame = 5.f;

    triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    triggerBox->SetGenerateOverlapEvents(true);
    triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelStreamerActor::OnOverlapBegin);
    triggerBox->OnComponentEndOverlap.AddDynamic(this, &ALevelStreamerActor::OnOverlapEnd);

    SetRootComponent(triggerBox);
}

// Called when the game starts or when spawned
void ALevelStreamerActor::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

        if(IsValid(playerController)) playerController->SetViewTarget(cameraPlayerMenu);
    }
}

void ALevelStreamerActor::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (!GetWorld())
        return;

    if (OtherActor->IsA<APlayerBeaver>())
    {
        ChangeCurrentLevel(gameLevel);

        StartTimerBeforeGameStarts();
    }
}

void ALevelStreamerActor::OnOverlapEnd(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                       int32 OtherBodyIndex)
{
    if (GetWorld() && menuLevel != NAME_None)
    {
        FLatentActionInfo actioninfo;
        UGameplayStatics::UnloadStreamLevel(GetWorld(), menuLevel, actioninfo, false);
    }
}

void ALevelStreamerActor::StartTimerBeforeGameStarts()
{
    if (!GetWorld()->GetAuthGameMode())
        return;

    FTimerHandle timerHandle;

    auto *ptrGameMode = StaticCast<ABeaverGameMode *>(UGameplayStatics::GetGameMode(GetWorld()));
    
    GetWorldTimerManager().SetTimer(timerHandle, ptrGameMode, &ABeaverGameMode::StartGame, timeBeforeStartGame, false);
}

void ALevelStreamerActor::ChangeCurrentLevel(const FName &levelName)
{
    if (IsValid(playerController) && levelName != NAME_None)
    {
        FLatentActionInfo actionInfo;
        FViewTargetTransitionParams transitionParams;

        UGameplayStatics::LoadStreamLevel(GetWorld(), levelName, true, false, actionInfo);

        transitionParams.BlendTime = customBlendTime;

        playerController->SetViewTarget(cameraPlayerInGame, transitionParams);
    }
}


