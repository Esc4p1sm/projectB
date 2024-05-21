// Copyright (c) 2024 Allure Games.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

ACameraDirector::ACameraDirector()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACameraDirector::BeginPlay()
{
    Super::BeginPlay();
    APlayerController *playerController = UGameplayStatics::GetPlayerController(this, 0);
    playerController->SetViewTarget(cameraPlayer);
}
