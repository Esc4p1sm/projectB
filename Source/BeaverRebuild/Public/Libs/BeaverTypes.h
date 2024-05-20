#pragma once

#include "BeaverTypes.generated.h"

class ABeaverGameMode;
class USkinsItemWidget;

// Alternative channel names
#define ECC_MARK_LOGS_TRACE_CHANNEL  ECC_GameTraceChannel1
#define ECC_CLIMBING_TRACE_CHANEL    ECC_GameTraceChannel2
#define ECC_LOGS_OBJECT_CHANNEL      ECC_GameTraceChannel3
#define ECC_HOURGLASS_OBJECT_CHANNEL ECC_GameTraceChannel4

// Delegate for changing the state of the game
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangeSignature, EBeaverGameState);

// Delegate of returning to the game from the wardrobe
DECLARE_MULTICAST_DELEGATE(FOnBackToGameSignature);

DECLARE_MULTICAST_DELEGATE(FOnBuyItemSignature);

UENUM(BlueprintType)
enum class EBeaverGameState : uint8
{
    Waiting = 0,
    InProgress,
    OptionsMenu,
    PauseMenu,
    WardrobeMenu,
    GameOver
};

UENUM(BlueprintType)
enum EItemTypes : uint8
{
    Null      = 0,
    HatType   = 1,
    BodyType  = 2,
    LevelType = 4,
    Classic   = 5,
    China     = 8,
    Space     = 16,
    Desert    = 32,
    Cemetery  = 64,
    Gold      = 128
};

USTRUCT(BlueprintType)
struct FSkinsData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    FName SkinName = NAME_None;

    UPROPERTY(EditAnywhere)
    UTexture2D* SkinPicture;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName LevelName = NAME_None;

    UPROPERTY(EditAnywhere)
    UStaticMesh* HatStaticMesh;

    UPROPERTY(EditAnywhere)
    USkeletalMesh* BeaverSkinSkeletalMesh;

    UPROPERTY(EditAnywhere)
    int32 Price;

    UPROPERTY(EditAnywhere)
    TEnumAsByte<EItemTypes> Category;

    UPROPERTY(EditAnywhere)
    TEnumAsByte<EItemTypes> Type;
};
