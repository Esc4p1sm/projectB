// Copyright (c) 2024 Allure Games.

#include "LevelStreamerActor.h"
#include "Components/BoxComponent.h"
#include "PlayerBeaver.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverGameInstance.h"
#include "Sound/SoundCue.h"

ALevelStreamerActor::ALevelStreamerActor()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelStreamerActor::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALevelStreamerActor::OnOverlapEnd);

    SetRootComponent(TriggerBox);
}

void ALevelStreamerActor::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    GameInstance     = StaticCast<UBeaverGameInstance*>(GetWorld()->GetGameInstance());

    if (IsValid(PlayerController))
    {
        PlayerController->SetViewTarget(CameraPlayerMenu);
    }
}

void ALevelStreamerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!GetWorld())
    {
        return;
    }

    if (OtherActor->IsA<APlayerBeaver>())
    {
        FName LevelForLoad = GameInstance->GetCurrentLevel();

        ChangeCurrentLevel(LevelForLoad);

        StartTimerBeforeGameStarts();
    }
}

void ALevelStreamerActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex)
{
    if (GetWorld() && MenuLevel != NAME_None)
    {
        FLatentActionInfo actioninfo;
        UGameplayStatics::UnloadStreamLevel(GetWorld(), MenuLevel, actioninfo, false);
        StaticCast<ABeaverGameMode*>(GetWorld()->GetAuthGameMode())->SetCurrentGameMusic(GameSound[GameInstance->GetCurrentLevel()]);
    }
}

void ALevelStreamerActor::StartTimerBeforeGameStarts()
{
    if (!GetWorld()->GetAuthGameMode())
    {
        return;
    }

    FTimerHandle TimerHandle;

    const auto GameMode = StaticCast<ABeaverGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));

    GetWorldTimerManager().SetTimer(TimerHandle, GameMode, &ABeaverGameMode::StartGame, TimeBeforeStartGame, false);
}

void ALevelStreamerActor::ChangeCurrentLevel(const FName& levelName)
{
    if (IsValid(PlayerController) && levelName != NAME_None)
    {
        FLatentActionInfo actionInfo;
        FViewTargetTransitionParams transitionParams;

        UGameplayStatics::LoadStreamLevel(GetWorld(), levelName, true, false, actionInfo);

        transitionParams.BlendTime = CustomBlendTime;

        PlayerController->SetViewTarget(CameraPlayerInGame, transitionParams);
    }
}
