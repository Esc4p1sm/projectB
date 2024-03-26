// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/WardrobeTrigger.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBeaver.h"
#include "BeaverPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverGameMode.h"
#include "Libs/BeaverTypes.h"
//#include "Components/TimelineComponent.h"
#include "Runtime/Engine/Classes/Curves/CurveFloat.h"

// Sets default values
AWardrobeTrigger::AWardrobeTrigger()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    triggerSphere                 = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
    timelineComp                  = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
    SetRootComponent(triggerSphere);
}

// Called when the game starts or when spawned
void AWardrobeTrigger::BeginPlay()
{
    Super::BeginPlay();

    triggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AWardrobeTrigger::OnOverlapBegin);
    triggerSphere->OnComponentEndOverlap.AddDynamic(this, &AWardrobeTrigger::OnOverlapEnd);
    beaver         =Cast<APlayerBeaver> (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    
    if (curveFloat)
    {
        UpdateFunctionFloat.BindDynamic(this, &AWardrobeTrigger::UpdateTimelineComp);
        timelineComp->AddInterpFloat(curveFloat,UpdateFunctionFloat);
    }
}

// Called every frame
void AWardrobeTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
   
   
}



void AWardrobeTrigger::UpdateTimelineComp(float Output)
{
    
    beaver->SetActorRelativeLocation(
        FVector{beaver->GetActorLocation().X, beaver->GetActorLocation().Y-Output, beaver->GetActorLocation().Z});
    
    
}

void AWardrobeTrigger::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    timelineComp->Play();

    Cast<ABeaverGameMode>(GetWorld()->GetAuthGameMode())->SetGameState(EBeaverGameState::WardrobeMenu);
    FViewTargetTransitionParams params;
    params.BlendTime = 3;
    UGameplayStatics::GetPlayerController(GetWorld(),0)->SetViewTarget(cameraPlayerWardrobe,params);
    beaver->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

void AWardrobeTrigger::OnOverlapEnd(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                    int32 OtherBodyIndex)
{
    ///* if (!GetWorld())
    //     return;

    // if (wardrobeWidget)
    // {
    //     wardrobeWidget->RemoveFromViewport();
    // }*/
}
