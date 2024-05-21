// Copyright (c) 2024 Allure Games.


#include "AchivementManager.h"

UAchivementManager::UAchivementManager(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAchivementManager::setSkins(uint8 hat, uint8 body, uint8 level)
{
    hatSkins   = hat;
    bodySkins  = body;
    levelSkins = level;
}

void UAchivementManager::setWorld(UWorld *gameWorld)
{
    world = gameWorld;
}

void UAchivementManager::CheckAchivements(EAchivementType achivementType)
{
    switch (achivementType)
    {
    case EAchivementType::BeaverTypeAchive:
        CheckBeaver();
        break;

    case EAchivementType::LogTypeAchive:
        CheckLogs();
        break;

    case EAchivementType::SkinTypeAchive:
        CheckSkins();
        break;

    case EAchivementType::EnvironmentTypeAchive:
        CheckEnvironment();
        break;
    }
}

void UAchivementManager::CheckBeaver()
{
    for (auto &achivement : beaverAchivements)
    {
        if (!achivement.isRound && !achivement.isCompleted)
        {
            float result;
            switch (achivement.type)
            {
            case EBeaverAchivementType::ClimbType:
                result = achivement.bIsGlobal ? globBeaverStats.maxOnWallTime : beaverStats.maxOnWallTime;
                break;

            case EBeaverAchivementType::DoubleJumpType:
                result = achivement.bIsGlobal ? globBeaverStats.doubleJumpsMade : beaverStats.doubleJumpsMade;
                break;
            case EBeaverAchivementType::FastLandType:
                result = achivement.bIsGlobal ? globBeaverStats.maxDives : beaverStats.maxDives;
                break;
            case EBeaverAchivementType::FlyType:
                result = achivement.bIsGlobal ? globBeaverStats.maxInAirTime : beaverStats.maxInAirTime;
                break;
            case EBeaverAchivementType::JumpType:
                result = achivement.bIsGlobal ? globBeaverStats.jumpsMade : beaverStats.jumpsMade;
                break;
            case EBeaverAchivementType::RunType:
                result = achivement.bIsGlobal ? globBeaverStats.maxOnGroundTime : beaverStats.maxOnGroundTime;
                break;
            default:
                GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Unknown beaver achivement")));
                continue;
            }

            if ((achivement.isNeedGreater && result > achivement.targetAmmount) ||
                !achivement.isNeedGreater && result < achivement.targetAmmount)
            {
                achivement.isCompleted = true;
                onAchivementReached.Broadcast(achivement);
            }
        }
    }
}

void UAchivementManager::CheckLogs()
{
    for (auto &achivement : logAchivements)
    {
        if (!achivement.isRound && !achivement.isCompleted)
        {
            int32 result;
            switch (achivement.type)
            {
            case ELogAchivementType::TotalLogType:
                result = achivement.bIsGlobal ? globLogStats.totalLogsJumped : logStats.totalLogsJumped;
                break;
            case ELogAchivementType::StandardLogType:
                result = achivement.bIsGlobal ? globLogStats.standardLogsJumped : logStats.standardLogsJumped;
                break;
            case ELogAchivementType::SwampLogType:
                result = achivement.bIsGlobal ? globLogStats.spoiledLogsJumped : logStats.spoiledLogsJumped;
                break;
            case ELogAchivementType::LogOfTimeType:
                result = achivement.bIsGlobal ? globLogStats.clockLogsJumped : logStats.clockLogsJumped;
                break;
            case ELogAchivementType::ShieldLogType:
                result = achivement.bIsGlobal ? globLogStats.tarLogsJumped : logStats.tarLogsJumped;
                break;
            case ELogAchivementType::HugeLogType:
                result = achivement.bIsGlobal ? globLogStats.giantLogsJumped : logStats.giantLogsJumped;
                break;
            case ELogAchivementType::GoldLogType:
                result = achivement.bIsGlobal ? globLogStats.goldLogsJumped : logStats.goldLogsJumped;
                break;
            default:
                GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Unknown log achivement")));
                continue;
            }
            if ((achivement.isNeedGreater && result > achivement.count) || !achivement.isNeedGreater && result < achivement.count)
            {
                achivement.isCompleted = true;
                onAchivementReached.Broadcast(achivement);
            }
        }
    }
}

void UAchivementManager::CheckEnvironment()
{
    for (auto &achivement : environmentAchivements)
    {
        if (!achivement.isRound && !achivement.isCompleted)
        {
            float result;
            switch (achivement.type)
            {
            case EEnvironmentAchivementType::DeflectType:
                result = achivement.bIsGlobal ? globEnvStats.logsDeflected : envStats.logsDeflected;
                break;
            case EEnvironmentAchivementType::ShieldType:
                result = achivement.bIsGlobal ? globEnvStats.totalShieldTime : envStats.maxShieldTime;
                break;
            case EEnvironmentAchivementType::TimeType:
                result = achivement.bIsGlobal ? globEnvStats.maxSlowedTime : envStats.maxSlowedTime;
                break;
            default:
                GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Unknown log achivement")));
                continue;
            }
            if ((achivement.isNeedGreater && result > achivement.targetAmount) ||
                !achivement.isNeedGreater && result < achivement.targetAmount)
            {
                achivement.isCompleted = true;
                onAchivementReached.Broadcast(achivement);
            }
        }
    }
}

void UAchivementManager::CheckSkins()
{
    for (auto &achivement : skinAchivements)
    {
        if ((achivement.type & ESkinAchivementType::HatTypeAchive) && (achivement.type & hatSkins))
        {
            achivement.isCompleted = true;
            onAchivementReached.Broadcast(achivement);
        }
        else if ((achivement.type & ESkinAchivementType::BodyTypeAchive) && (achivement.type & bodySkins))
        {
            achivement.isCompleted = true;
            onAchivementReached.Broadcast(achivement);
        }
        else if ((achivement.type & ESkinAchivementType::LevelTypeAchive) && (achivement.type & levelSkins))
        {
            achivement.isCompleted = true;
            onAchivementReached.Broadcast(achivement);
        }
    }
}

void UAchivementManager::saveStatistic()
{
    FString savePath = FPaths::ProjectDir();
    savePath += "/Statistic/statistic_";
    savePath += FDateTime::UtcNow().ToString();
    savePath += ".txt";
    FFileHelper::SaveStringToFile(statString, *savePath);
}

void UAchivementManager::addSaveString()
{
    ++inGameMins;
    statString += "In game time: " + FString::FromInt(inGameMins) + " minutes" + "\n";
    
    statString += "Standard logs jumped: " + FString::FromInt(logStats.standardLogsJumped) + "\n";
    statString += "Golden logs jumped: " + FString::FromInt(logStats.goldLogsJumped) + "\n";
    statString += "Swamp logs jumped: " + FString::FromInt(logStats.spoiledLogsJumped) + "\n";
    statString += "Huge logs jumped: " + FString::FromInt(logStats.giantLogsJumped) + "\n";
    statString += "Tar logs jumped: " + FString::FromInt(logStats.tarLogsJumped) + "\n";
    statString += "Time logs jumped: " + FString::FromInt(logStats.clockLogsJumped) + "\n";
    statString += "Total logs jumped: " + FString::FromInt(logStats.totalLogsJumped) + "\n";
    statString += "\n";
    statString += "Jumps: " + FString::FromInt(beaverStats.jumpsMade) + "\n";
    statString += "Double jumps: " + FString::FromInt(beaverStats.doubleJumpsMade) + "\n";
    statString += "Dive landings: " + FString::FromInt(beaverStats.maxDives) + "\n";
    statString += "Wall jumps: " + FString::FromInt(beaverStats.wallLaunched) + "\n";
    statString += "Max in air time: " + FString::FromInt(beaverStats.maxInAirTime) + "\n";
    statString += "Max on ground time: " + FString::FromInt(beaverStats.maxOnGroundTime) + "\n";
    statString += "Max on wall time: " + FString::FromInt(beaverStats.maxOnWallTime) + "\n";
    statString += "Total in air time: " + FString::FromInt(beaverStats.totalInAirTime) + "\n";
    statString += "Total on ground time: " + FString::FromInt(beaverStats.totalOnGroundTime) + "\n";
    statString += "Total on wall time: " + FString::FromInt(beaverStats.totalOnWallTime) + "\n";
    statString += "\n";
    statString += "Hourglasses collected: " + FString::FromInt(envStats.hourglassesCollected) + "\n";
    statString += "Shields collected: " + FString::FromInt(envStats.shieldsCollected) + "\n";
    statString += "Logs deflected: " + FString::FromInt(envStats.logsDeflected) + "\n";
    statString += "Total shield time: " + FString::FromInt(envStats.totalShieldTime) + "\n";
    statString += "Total slowdown time: " + FString::FromInt(envStats.totalSlowedTime) + "\n";
    statString += "\n\n";
}

void UAchivementManager::addFinalString()
{
    statString += "RoundStats\n";
    auto secsLeft = world->GetTimerManager().GetTimerElapsed(gameTimer);
    statString += "Round duration: " + FString::FromInt(inGameMins) + " minuts" + FString::FromInt(secsLeft) + " seconds" + "\n";

    statString += "Standard logs jumped: " + FString::FromInt(logStats.standardLogsJumped) + "\n";
    statString += "Golden logs jumped: " + FString::FromInt(logStats.goldLogsJumped) + "\n";
    statString += "Swamp logs jumped: " + FString::FromInt(logStats.spoiledLogsJumped) + "\n";
    statString += "Huge logs jumped: " + FString::FromInt(logStats.giantLogsJumped) + "\n";
    statString += "Tar logs jumped: " + FString::FromInt(logStats.tarLogsJumped) + "\n";
    statString += "Time logs jumped: " + FString::FromInt(logStats.clockLogsJumped) + "\n";
    statString += "Total logs jumped: " + FString::FromInt(logStats.totalLogsJumped) + "\n";
    statString += "\n";
    statString += "Jumps: " + FString::FromInt(beaverStats.jumpsMade) + "\n";
    statString += "Double jumps: " + FString::FromInt(beaverStats.doubleJumpsMade) + "\n";
    statString += "Dive landings: " + FString::FromInt(beaverStats.maxDives) + "\n";
    statString += "Wall jumps: " + FString::FromInt(beaverStats.wallLaunched) + "\n";
    statString += "Max in air time: " + FString::FromInt(beaverStats.maxInAirTime) + "\n";
    statString += "Max on ground time: " + FString::FromInt(beaverStats.maxOnGroundTime) + "\n";
    statString += "Max on wall time: " + FString::FromInt(beaverStats.maxOnWallTime) + "\n";
    statString += "Total in air time: " + FString::FromInt(beaverStats.totalInAirTime) + "\n";
    statString += "Total on ground time: " + FString::FromInt(beaverStats.totalOnGroundTime) + "\n";
    statString += "Total on wall time: " + FString::FromInt(beaverStats.totalOnWallTime) + "\n";
    statString += "\n";
    statString += "Hourglasses collected: " + FString::FromInt(envStats.hourglassesCollected) + "\n";
    statString += "Shields collected: " + FString::FromInt(envStats.shieldsCollected) + "\n";
    statString += "Logs deflected: " + FString::FromInt(envStats.logsDeflected) + "\n";
    statString += "Total shield time: " + FString::FromInt(envStats.totalShieldTime) + "\n";
    statString += "Total slowdown time: " + FString::FromInt(envStats.totalSlowedTime) + "\n";
    statString += "\n\n";
    statString += "\nGlobal statistic\n";

    statString += "Standard logs jumped: " + FString::FromInt(globLogStats.standardLogsJumped) + "\n";
    statString += "Golden logs jumped: " + FString::FromInt(globLogStats.goldLogsJumped) + "\n";
    statString += "Swamp logs jumped: " + FString::FromInt(globLogStats.spoiledLogsJumped) + "\n";
    statString += "Huge logs jumped: " + FString::FromInt(globLogStats.giantLogsJumped) + "\n";
    statString += "Tar logs jumped: " + FString::FromInt(globLogStats.tarLogsJumped) + "\n";
    statString += "Time logs jumped: " + FString::FromInt(globLogStats.clockLogsJumped) + "\n";
    statString += "Total logs jumped: " + FString::FromInt(globLogStats.totalLogsJumped) + "\n";
    statString += "\n";
    statString += "Jumps: " + FString::FromInt(globBeaverStats.jumpsMade) + "\n";
    statString += "Double jumps: " + FString::FromInt(globBeaverStats.doubleJumpsMade) + "\n";
    statString += "Dive landings: " + FString::FromInt(globBeaverStats.maxDives) + "\n";
    statString += "Wall jumps: " + FString::FromInt(globBeaverStats.wallLaunched) + "\n";
    statString += "Max in air time: " + FString::FromInt(globBeaverStats.maxInAirTime) + "\n";
    statString += "Max on ground time: " + FString::FromInt(globBeaverStats.maxOnGroundTime) + "\n";
    statString += "Max on wall time: " + FString::FromInt(globBeaverStats.maxOnWallTime) + "\n";
    statString += "Total in air time: " + FString::FromInt(globBeaverStats.totalInAirTime) + "\n";
    statString += "Total on ground time: " + FString::FromInt(globBeaverStats.totalOnGroundTime) + "\n";
    statString += "Total on wall time: " + FString::FromInt(globBeaverStats.totalOnWallTime) + "\n";
    statString += "\n";
    statString += "Hourglasses collected: " + FString::FromInt(globEnvStats.hourglassesCollected) + "\n";
    statString += "Shields collected: " + FString::FromInt(globEnvStats.shieldsCollected) + "\n";
    statString += "Logs deflected: " + FString::FromInt(globEnvStats.logsDeflected) + "\n";
    statString += "Total shield time: " + FString::FromInt(globEnvStats.totalShieldTime) + "\n";
    statString += "Total slowdown time: " + FString::FromInt(globEnvStats.totalSlowedTime) + "\n";
    statString += "\n\n";
}

void UAchivementManager::startCountStat()
{
    if (world)
    {
        ClearStatistic();
        statString = "Statistic for" + FDateTime::UtcNow().ToString() + "\n";
        world->GetTimerManager().SetTimer(gameTimer, this, &UAchivementManager::addSaveString, 60.0, true);
    }
}

void UAchivementManager::CountLogStats(TEnumAsByte<ELogType> TypeOfLog)
{
    GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("Log counted")));
    ++logStats.totalLogsJumped;
    auto type = TypeOfLog.GetValue();
    switch (type)
    {
    case StandardLog:
        ++logStats.standardLogsJumped;
        break;

    case SwampLog:
        ++logStats.spoiledLogsJumped;
        break;

    case ClockedLog:
        ++logStats.clockLogsJumped;
        break;

    case GoldLog:
        ++logStats.goldLogsJumped;
        break;

    case TarLog:
        ++logStats.tarLogsJumped;
        break;

    case HugeLog:
        ++logStats.giantLogsJumped;
        break;

    default:
        break;
    }
    CheckLogs();
}

void UAchivementManager::ClearStatistic()
{
    logStats.totalLogsJumped    = 0;
    logStats.standardLogsJumped = 0;
    logStats.clockLogsJumped    = 0;
    logStats.giantLogsJumped    = 0;
    logStats.goldLogsJumped     = 0;
    logStats.spoiledLogsJumped  = 0;
    logStats.tarLogsJumped      = 0;

    beaverStats.jumpsMade         = 0;
    beaverStats.doubleJumpsMade   = 0;
    beaverStats.maxDives          = 0;
    beaverStats.maxInAirTime      = 0.0f;
    beaverStats.maxOnGroundTime   = 0.0f;
    beaverStats.maxOnWallTime     = 0.0f;
    beaverStats.totalInAirTime    = 0.0f;
    beaverStats.totalOnGroundTime = 0.0f;
    beaverStats.totalOnWallTime   = 0.0f;

    envStats.hourglassesCollected = 0;
    envStats.logsDeflected        = 0;
    envStats.shieldsCollected     = 0;
    envStats.maxShieldTime        = 0.0f;
    envStats.maxSlowedTime        = 0.0f;
    envStats.totalShieldTime      = 0.0f;
    envStats.totalSlowedTime      = 0.0f;
    envStats.curShieldTime        = 0.0f;
    envStats.curSlowedTime        = 0.0f;
}

void UAchivementManager::CountBeaverStats(BeaverState newState)
{
    switch (newState)
    {
    case BeaverState::isJumped:
        ++beaverStats.jumpsMade;
        if (!inAirTimer.IsValid()&&world)
        {
            world->GetGameInstance()->GetTimerManager().SetTimer(inAirTimer, this, &UAchivementManager::CheckTimers, 1.0f, true);
        }
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Beaver has jumped");
        break;

    case BeaverState::isLanded:
        if (!onGroundTimer.IsValid() && world)
        {
            world->GetGameInstance()->GetTimerManager().SetTimer(onGroundTimer, this, &UAchivementManager::CheckTimers, 1.0f, true);
        }
        if (inAirTimer.IsValid() && world)
        {
                float timeElapsed = world->GetGameInstance()->GetTimerManager().GetTimerElapsed(inAirTimer);
                beaverStats.totalInAirTime += timeElapsed;
                curInAirTime += timeElapsed;
                if (curInAirTime > beaverStats.maxInAirTime)
                {
                    beaverStats.maxInAirTime = curInAirTime;
                }
                curInAirTime = 0.0f;
        }
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Beaver has landed");
        break;

    case BeaverState::isLaunched:
        ++beaverStats.wallLaunched;
        if (onWallTimer.IsValid() && world)
        {

                float timeElapsed = world->GetGameInstance()->GetTimerManager().GetTimerElapsed(onWallTimer);
                beaverStats.totalOnWallTime += timeElapsed;
                curOnWallTime += timeElapsed;
                if (curOnWallTime > beaverStats.maxOnWallTime)
                {
                    ++beaverStats.maxOnWallTime;
                }
                curOnWallTime = 0.0f;
        }
        if (world && world->GetGameInstance()->GetTimerManager().IsTimerPaused(inAirTimer))
        {
            world->GetGameInstance()->GetTimerManager().UnPauseTimer(inAirTimer);
        }
        else if (world && !inAirTimer.IsValid())
        {
            world->GetGameInstance()->GetTimerManager().SetTimer(inAirTimer, this, &UAchivementManager::CheckTimers, 1.0f, true);
        }
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Beaver is launched");
        break;

    case BeaverState::isClimbing:
        if (!onWallTimer.IsValid() && world)
        {
            world->GetGameInstance()->GetTimerManager().SetTimer(onWallTimer, this, &UAchivementManager::CheckTimers, 1.0f, true);
        }
        if (inAirTimer.IsValid() && world)
        {
            world->GetGameInstance()->GetTimerManager().PauseTimer(inAirTimer);
        }
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Beaver is climbing");
        break;

    case BeaverState::isFastLanding:
        ++beaverStats.maxDives;
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Beaver has dived");
        break;

    default:
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Unknown beaver state");
        break;
    }
    CheckBeaver();
}

void UAchivementManager::CountEnvironmentEvent(EnvironmentEvent event)
{
    switch (event)
    {
    case EnvironmentEvent::TimeSlowed:
        ++envStats.hourglassesCollected;
        if (!slowedTimer.IsValid() && world)
        {
            world->GetGameInstance()->GetTimerManager().SetTimer(slowedTimer, this, &UAchivementManager::CheckTimers, 1.0f, true);
            currSlowTime = 0.0f;
        }
        break;
    case EnvironmentEvent::TimeRestored:
        if (slowedTimer.IsValid() && world)
        {
            float timeElapsed = world->GetGameInstance()->GetTimerManager().GetTimerElapsed(slowedTimer);
            envStats.totalSlowedTime += timeElapsed;
            currSlowTime += timeElapsed;
            if (currSlowTime > envStats.maxSlowedTime)
            {
                envStats.maxSlowedTime = currSlowTime;
            }
            slowedTimer.Invalidate();
        }
        break;
    case EnvironmentEvent::ShieldBeging:
        ++envStats.shieldsCollected;
        if (!shieldTimer.IsValid() && world)
        {
            world->GetGameInstance()->GetTimerManager().SetTimer(shieldTimer, this, &UAchivementManager::CheckTimers, 1.0f, true);
            currShieldTime = 0.0f;
        }
        break;
    case EnvironmentEvent::ShieldEnd:
        if (shieldTimer.IsValid() && world)
        {
            envStats.totalShieldTime += world->GetGameInstance()->GetTimerManager().GetTimerElapsed(shieldTimer);
            currShieldTime += world->GetGameInstance()->GetTimerManager().GetTimerElapsed(shieldTimer);
            if (currShieldTime > envStats.maxShieldTime)
            {
                envStats.maxShieldTime = currShieldTime;
            }
            shieldTimer.Invalidate();
        }
        break;
    }
    CheckEnvironment();
}

void UAchivementManager::CheckTimers()
{
    if (slowedTimer.IsValid())
    {
        currSlowTime += 1.0f;
        envStats.totalSlowedTime += 1.0f;
    }
    if (shieldTimer.IsValid())
    {
        currSlowTime += 1.0f;
        envStats.totalShieldTime += 1.0f;
    }
    if (onGroundTimer.IsValid())
    {
        beaverStats.totalOnGroundTime += 1.0f;
        curOnGroundTime += 1.0f;
    }
    if (inAirTimer.IsValid())
    {
        beaverStats.totalInAirTime += 1.0f;
        curInAirTime += 1.0f;
    }
    if (onWallTimer.IsValid())
    {
        beaverStats.totalOnWallTime += 1.0f;
        curOnWallTime += 1.0f;
    }
}