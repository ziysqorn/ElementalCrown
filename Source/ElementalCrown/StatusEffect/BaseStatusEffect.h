// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"

/**
 * 
 */

class ABaseCharacter;

class ELEMENTALCROWN_API BaseStatusEffect
{
protected:

	FName StatusName;

	float AffectingTime;

	UPaperSprite* StatusAvt = nullptr;

	ABaseCharacter* OwningCharacter = nullptr;

	ABaseCharacter* AffectedCharacter = nullptr;

	FTimerHandle EffectHandle;
public:
	BaseStatusEffect();
	BaseStatusEffect(const TCHAR* AvtRef);
	virtual ~BaseStatusEffect() {};
	FName GetStatusName() {
		return StatusName;
	}
	void SetOwningCharacter(ABaseCharacter* Character) {
		OwningCharacter = Character;
	}
	void SetAffectedCharacter(ABaseCharacter* Character) {
		AffectedCharacter = Character;
	}
	virtual void ExecuteStatus() {};
};
