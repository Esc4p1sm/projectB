// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamiteComponent.h"
#include "PlayerBeaver.h"
#include "Dynamite.h"

UDynamiteComponent::UDynamiteComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDynamiteComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDynamiteComponent::SpawnDynamite(ABeaverLog* Log)
{
    if (!GetWorld())
    {
        return;
    }

	const auto PlayerBeaver = StaticCast<APlayerBeaver*>(GetOwner());

    if (!IsValid(PlayerBeaver))
    {
        return;
    }

	const auto Dynamite = GetWorld()->SpawnActor<ADynamite>(DynamiteClass/*, PlayerBeaver->GetMesh()->GetSocketLocation("DynamiteSocket"),FRotator::ZeroRotator*/);
    
    if (!IsValid(Dynamite))
    {
        return;
    }

    FAttachmentTransformRules AttachmentTransformRules{EAttachmentRule::SnapToTarget,false};
    FDetachmentTransformRules DetachmentTransformRules{EDetachmentRule::KeepWorld, false};

    Dynamite->AttachToComponent(PlayerBeaver->GetMesh(), AttachmentTransformRules, "DynamiteSocket");
    Dynamite->DetachFromActor(DetachmentTransformRules);
    Dynamite->FollowLog = Log;
}




