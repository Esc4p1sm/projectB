// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenBeaverLog.h"
#include "BeaverGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AGoldenBeaverLog::BeginPlay()
{
    Super::BeginPlay();
    scaleSpeed = 2.5f;
}

void AGoldenBeaverLog::BeaverLogSlivers()
{
    Cast<UBeaverGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->AddSlivers(5);
}
