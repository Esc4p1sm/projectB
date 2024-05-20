// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenBeaverLog.h"
#include "BeaverGameInstance.h"
#include "Kismet/GameplayStatics.h"

AGoldenBeaverLog::AGoldenBeaverLog()
{
    LogParams.ScaleSpeed = 2.5;
    LogParams.TypeOfLog  = ELogType::GoldLog;
}
