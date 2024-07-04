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

	UPaperFlipbookComponent* StatusFlipbookComp = nullptr;

	UPaperSprite* StatusAvt = nullptr;

	UPaperFlipbook* StatusFlipbook = nullptr;

	ABaseCharacter* OwningCharacter = nullptr;

	ABaseCharacter* AffectedCharacter = nullptr;

	FTimerHandle EffectEndHandle;
public:
	BaseStatusEffect();
	BaseStatusEffect(const TCHAR* AvtRef, const TCHAR* FlipbookRef);
	virtual ~BaseStatusEffect();
	FName GetStatusName() {
		return StatusName;
	}
	void SetOwningCharacter(ABaseCharacter* Character) {
		OwningCharacter = Character;
	}
	void SetAffectedCharacter(ABaseCharacter* Character) {
		AffectedCharacter = Character;
	}
	virtual void SetAvtFromRef(const TCHAR* AvtRef);
	virtual void ExecuteStatus() {};
};
