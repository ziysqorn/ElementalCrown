// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../StatusEffect/BurnStatus.h"
#include "../StatusEffect/BleedStatus.h"
#include "../StatusEffect/DrowsyStatus.h"
#include "../StatusEffect/StunStatus.h"

/**
 * 
 */

class BaseCharacter;

class ELEMENTALCROWN_API Elemental
{
protected:
	//Elemental name
	FName ElementalName;
	ABaseCharacter* OwningCharacter;
	int ApplyEffectChanceRange = 0;
public:
	//Constructor
	Elemental();
	//Destructor
	virtual ~Elemental();
	virtual void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) {}
	void SetOwningCharacter(ABaseCharacter* Character) {
		if (Character) OwningCharacter = Character;
	}
	FName GetName() { return ElementalName; }
};
class Fire :public Elemental {
public:
	Fire();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) override;
};
class Water :public Elemental {
public:
	Water();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) override;
};
class Earth : public Elemental {
public:
	Earth();
	void ApplyStunEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup);
};
class Metal : public Elemental {
public:
	Metal();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) override;
};
class Plant : public Elemental {
public:
	Plant();
	void ApplyDrowsyEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup);
};


