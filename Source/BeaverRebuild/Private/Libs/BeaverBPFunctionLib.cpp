// Fill out your copyright notice in the Description page of Project Settings.

#include "Libs/BeaverBPFunctionLib.h"
#include "Sound/SoundClass.h"

FVector UBeaverBPFunctionLib::MakeRandomDirection(float MinAngle, float MaxAngle)
{
    FVector Direction(0.f, 0.f, -1.f);

    const float RandAngle = FMath::RandRange(MinAngle, MaxAngle);
    Direction             = Direction.RotateAngleAxis(RandAngle, FVector(1.f, 0.f, 0.f));

    if (FMath::RandBool())
    {
        Direction.Y *= -1;
    }

    return Direction;
}

void UBeaverBPFunctionLib::SetVolumeGameplaySound(USoundClass* GameplaySoundClass, float Volume)
{
    if (!GameplaySoundClass)
    {
        return;
    }

    Volume *= 0.01f;
    GameplaySoundClass->Properties.Volume = FMath::Clamp(Volume, 0, 1);
}

void UBeaverBPFunctionLib::SetVolumeGameMusic(USoundClass* GameMusicSoundClass, float Volume)
{
    if (!GameMusicSoundClass)
    {
        return;
    }

    Volume *= 0.01f;
    GameMusicSoundClass->Properties.Volume = FMath::Clamp(Volume, 0, 1);
}

float UBeaverBPFunctionLib::GetVolumeGameMusic(USoundClass* GameMusicSoundClass)
{
    if (!GameMusicSoundClass)
    {
        return 0;
    }

    return GameMusicSoundClass->Properties.Volume;
}

float UBeaverBPFunctionLib::GetVolumeGameplaySound(USoundClass* GameplaySoundClass)
{
    if (!GameplaySoundClass)
    {
        return 0;
    }

    return GameplaySoundClass->Properties.Volume;
}
