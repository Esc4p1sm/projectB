// Fill out your copyright notice in the Description page of Project Settings.

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
