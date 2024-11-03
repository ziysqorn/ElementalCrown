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
	UElemental(const TCHAR* Ref);
	virtual void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) {}
	FName GetName() { return ElementalName; }
};


UCLASS()
class UFire :public UElemental {
	GENERATED_BODY()
public:
	UFire();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
};


UCLASS()
class UWater :public UElemental {
	GENERATED_BODY()
public:
	UWater();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
};


UCLASS()
class UEarth : public UElemental {
	GENERATED_BODY()
public:
	UEarth();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
};


UCLASS()
class UMetal : public UElemental {
	GENERATED_BODY()
public:
	UMetal();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
};


UCLASS()
class UPlant : public UElemental {
	GENERATED_BODY()
public:
	UPlant();
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup) override;
};


