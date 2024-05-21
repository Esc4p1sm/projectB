// Copyright (c) 2024 Allure Games.

#include "BeaverLogSwamp.h"
#include "BeaverGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ABeaverLogSwamp::ABeaverLogSwamp()
{
    SwampAdditionalTime = 5.f;

    ABeaverLogSwamp::CapsuleComponent->OnComponentHit.AddDynamic(this, &ABeaverLogSwamp::OnComponentHit);
    LogParams.TypeOfLog = ELogType::SwampLog;
}

void ABeaverLogSwamp::OnComponentHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                     FVector NormalImpulse, const FHitResult &Hit)
{
    if (IsValid(GetWorld()) && OtherActor->IsA(APlayerBeaver::StaticClass()))
    {
        StaticCast<ABeaverGameMode *>(UGameplayStatics::GetGameMode(GetWorld()))->AddLifeTime(SwampAdditionalTime);
        Destroy();
    } 
}
