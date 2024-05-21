// Copyright (c) 2024 Allure Games.

#include "Dynamite.h"
#include "BeaverLog.h"

ADynamite::ADynamite()
{
    PrimaryActorTick.bCanEverTick = true;
    StaticMeshComponent           = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
    TimeLineComponent             = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLineComponent"));
}

void ADynamite::BeginPlay()
{
    Super::BeginPlay();

    CurrentDynamiteLocation = GetActorLocation();

    if (CurveFloat)
    {
        FOnTimelineFloat FunctionFloatDelegate;

        FunctionFloatDelegate.BindDynamic(this, &ADynamite::UpdateTimelineComp);

        TimeLineComponent->AddInterpFloat(CurveFloat, FunctionFloatDelegate);
    }

    TimeLineComponent->Play();
}

void ADynamite::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADynamite::UpdateTimelineComp(float Alpha)
{
    const FVector FollowDirection = FMath::Lerp(this->GetActorLocation(), FollowLog->GetActorLocation(), Alpha * FollowingSpeed);

    if (FollowLog)
    {
        this->SetActorLocation(FollowDirection);
    }
}
