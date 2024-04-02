#pragma once

#include "Enums.generated.h"

UENUM(BlueprintType)
enum class CharacterState : uint8
{
	NONE UMETA(DisplayName = "None"),
	IDLE UMETA(DisplayName = "Idle"),
	MOVE UMETA(DisplayName = "Moving"),
	ATTACK UMETA(DisplayName = "Attacking"),
	USESKILL UMETA(DisplayName = "Using skill"),
	SHOOT UMETA(DisplayName = "Shooting"),
	SLIDE UMETA(DisplayName = "Sliding"),
	DODGE UMETA(DisplayName = "Dodging"),
	HURT UMETA(DisplayName = "Hurt"),
	STUNNED UMETA(DisplayName = "Stunned"),
	DEATH UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class WeaponType : uint8
{
	WEAPON_SWORD UMETA(DisplayName = "Weapon_Sword"),
	WEAPON_HAND UMETA(DisplayName = "Weapon_Hand")
};
