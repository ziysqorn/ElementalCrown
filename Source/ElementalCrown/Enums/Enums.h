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
	DEATH UMETA(DisplayName = "Dead"),
	STUN UMETA(DisplayName = "Stun"),
	AIRBORNE UMETA(DisplayName = "Airborne"),
	SURF UMETA(DisplayName = "Surfing"),
};

UENUM(BlueprintType)
enum class ConsumableType : uint8 {
	HEALPOTION UMETA(DisplayName = "Heal Potion"),
	MANAPOTION UMETA(DisplayName = "Mana Potion"),
	BLEEDCUREPOTION UMETA(DisplayName = "Bleed Cure Potion"),
	BURNCUREPOTION UMETA(DisplayName = "Burn Cure Potion"),
	DROWSYCUREPOTION UMETA(DisplayName = "Drowsy Cure Potion"),
	STUNCUREPOTION UMETA(DisplayName = "Stun Cure Potion"),
	VULNERABLECUREPOTION UMETA(DisplayName = "Vulnerable Cure Potion")
};