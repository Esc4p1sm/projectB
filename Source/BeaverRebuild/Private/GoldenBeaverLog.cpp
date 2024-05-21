// Copyright (c) 2024 Allure Games.


#include "GoldenBeaverLog.h"
#include "BeaverGameInstance.h"
#include "Kismet/GameplayStatics.h"

AGoldenBeaverLog::AGoldenBeaverLog()
{
    LogParams.ScaleSpeed = 2.5;
    LogParams.TypeOfLog  = ELogType::GoldLog;
}
