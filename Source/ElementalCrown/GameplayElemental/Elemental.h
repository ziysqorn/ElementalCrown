// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../StatusEffect/BurnStatus.h"
#include "../StatusEffect/BleedStatus.h"
#include "../StatusEffect/DrowsyStatus.h"
#include "../StatusEffect/StunStatus.h"
#include "../StatusEffect/VulnerableStatus.h"
#include "Elemental.generated.h"

/**
 * 
 */

class BaseCharacter;

UCLASS()
class ELEMENTALCROWN_API UElemental : public UObject
{
	GENERATED_BODY()
protected:
	//Elemental name
	FName ElementalName;
public:
	//Constructor
	UElemental();
	virtual void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) {}
	virtual float CalcDmgByStrongerElemental(UElemental* inElemental) {
		return 0.0f;
	}
	FName GetName() { return ElementalName; }
};


UCLASS()
class ELEMENTALCROWN_API UFire :public UElemental {
	GENERATED_BODY()
public:
	UFire();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
	float CalcDmgByStrongerElemental(UElemental* inElemental) override {
		if (inElemental) {
			if (inElemental->GetName().IsEqual("Water")) return 1.5f;
		}
		return 0.0f;
	}
};


UCLASS()
class ELEMENTALCROWN_API UWater :public UElemental {
	GENERATED_BODY()
public:
	UWater();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
	float CalcDmgByStrongerElemental(UElemental* inElemental) override {
		if (inElemental) {
			if (inElemental->GetName().IsEqual("Earth")) return 1.5f;
		}
		return 0.0f;
	}
};


UCLASS()
class ELEMENTALCROWN_API UEarth : public UElemental {
	GENERATED_BODY()
public:
	UEarth();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
	float CalcDmgByStrongerElemental(UElemental* inElemental) override {
		if (inElemental) {
			if (inElemental->GetName().IsEqual("Plant")) return 1.5f;
		}
		return 0.0f;
	}
};


UCLASS()
class ELEMENTALCROWN_API UMetal : public UElemental {
	GENERATED_BODY()
public:
	UMetal();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
	float CalcDmgByStrongerElemental(UElemental* inElemental) override {
		if (inElemental) {
			if (inElemental->GetName().IsEqual("Fire")) return 1.5f;
		}
		return 0.0f;
	}
};


UCLASS()
class ELEMENTALCROWN_API UPlant : public UElemental {
	GENERATED_BODY()
public:
	UPlant();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
	float CalcDmgByStrongerElemental(UElemental* inElemental) override {
		if (inElemental) {
			if (inElemental->GetName().IsEqual("Metal")) return 1.5f;
		}
		return 0.0f;
	}
};


