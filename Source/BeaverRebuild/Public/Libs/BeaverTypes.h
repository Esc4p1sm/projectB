#pragma once
#include "BeaverTypes.generated.h"

#define ECC_MarkLogsTraceChannel ECC_GameTraceChannel1
#define ECC_ClimbingTraceChannel ECC_GameTraceChannel2
#define ECC_LogsObjectChannel ECC_GameTraceChannel3
#define ECC_HourglassObjectChannel ECC_GameTraceChannel4

class ABeaverGameMode;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangeSignature, EBeaverGameState);

UENUM(BlueprintType)
enum class EBeaverGameState:uint8
{
	Waiting=0,
	InProgress,
	PauseOptions,
	PauseMenu,
	WardrobeMenu,
	GameOver
};

