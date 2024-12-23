// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Effects/StatusEffect/BaseStatus.h"

/**
 * 
 */

class ABaseCharacter;


class ELEMENTALCROWN_API BaseStatusEffect
{
protected:
	FName StatusName;

	float TimeElapsed = 0.0f;

	float AffectingTime;

	ABaseStatus* StatusEffectActor = nullptr;

	ABaseCharacter* OwningChar = nullptr;

	ABaseCharacter* AffectedChar = nullptr;

	FTimerHandle EffectHandle;

	FTimerHandle ResetHandle;

	bool isActivated = false;

	float CurrentProgress = 0.0f;

	float BuildupToFill = 10.0f;

	float TimeForAReset;
public:
	BaseStatusEffect();
	virtual ~BaseStatusEffect();
	FName GetStatusName() const { 
		return StatusName; 
	}
	const bool GetActivateStatus() { 
		return isActivated; 
	}
	float* GetCurrentProgress() {
		return &CurrentProgress;
	}
	const float GetBuildupPercentage() { 
		return CurrentProgress / BuildupToFill; 
	}
	const float GetTimePercentage() { 
		return (AffectingTime - TimeElapsed) / AffectingTime; 
	}
	void SetOwningCharacter(ABaseCharacter* Character) {
		OwningChar = Character;
	}
	void SetAffectedCharacter(ABaseCharacter* Character) {
		AffectedChar = Character;
	}
	virtual void BuildingUp(ABaseCharacter* OwningCharacter, const float& inBuildup);
	virtual void ExecuteStatus() {};
};
