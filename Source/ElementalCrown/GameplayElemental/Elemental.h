// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../StatusEffect/BurnStatus.h"
#include "../StatusEffect/BleedStatus.h"

/**
 * 
 */

class BaseCharacter;

class ELEMENTALCROWN_API Elemental
{
protected:
	//Elemental name
	FName ElementalName;
	int ApplyEffectChanceRange = 0;
	ABaseCharacter* OwningCharacter = nullptr;
public:
	//Constructor
	Elemental();
	Elemental(ABaseCharacter* character);
	Elemental(const Elemental &other) {
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	//Destructor
	virtual ~Elemental();
	//Print test
	virtual void TestType() {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
		UE_LOG(LogTemp, Log, TEXT("%s"), *FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
	};
	virtual void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) {}
	FName GetName() { return ElementalName; }

};
class Fire :public Elemental {
public:
	Fire();
	Fire(ABaseCharacter* character);
	Fire(const Fire& other) {
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) override;
};
class Water :public Elemental {
public:
	Water();
	Water(ABaseCharacter* character);
	Water(const Water& other) {
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) override;
};
class Earth : public Elemental {
public:
	Earth();
	Earth(ABaseCharacter* character);
	Earth(const Earth& other) {
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
};
class Metal : public Elemental {
public:
	Metal();
	Metal(ABaseCharacter* character);
	Metal(const Metal& other) {
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ApplyStatusEffect(ABaseCharacter* AffectedCharacter) override;
};
class Plant : public Elemental {
public:
	Plant();
	Plant(ABaseCharacter* character);
	Plant(const Plant& other) {
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
};


