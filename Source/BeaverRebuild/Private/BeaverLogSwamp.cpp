// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverLogSwamp.h"
#include "BeaverGameMode.h"
#include "Kismet/GameplayStatics.h"

//
//void ABeaverLogSwamp::LogMove(float DeltaTime)
//{
//   Super::LogMove(DeltaTime);
//}

void ABeaverLogSwamp::MarkAsJumped()
{
    if (!bIsJumped)
    {
        bIsJumped = true;
        Super::BeaverLogSlivers();
        GetWorldTimerManager().SetTimer(timerHandle, this, &ABeaverLogSwamp::BeaverLogScore, 2);
    }
}

void ABeaverLogSwamp::BeaverLogScore()
{
    //Cast<ABeaverGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddScore(1);
    Cast<ABeaverGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddLifeTime(-10);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("minus"));
    Destroy();
}
