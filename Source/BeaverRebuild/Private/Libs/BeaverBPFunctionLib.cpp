// Fill out your copyright notice in the Description page of Project Settings.


#include "Libs/BeaverBPFunctionLib.h"

FVector UBeaverBPFunctionLib::MakeRandomDirection(float minAngle,float maxAngle)
{
    FVector direction(0.f, 0.f, -1.f);

    const float randAngle = FMath::RandRange(minAngle,maxAngle);
    direction       = direction.RotateAngleAxis(randAngle, FVector(1.f, 0.f, 0.f));

    if (FMath::RandBool())
    {
        direction.Y *= -1;
    }

    return direction;
}