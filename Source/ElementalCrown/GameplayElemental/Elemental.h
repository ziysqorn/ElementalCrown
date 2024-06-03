// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Characters/BaseCharacter/BaseCharacter.h"
#include "CoreMinimal.h"

/**
 * 
 */
class ABaseCharacter;
class ELEMENTALCROWN_API Elemental
{
protected:
	int Buff{0};
	//Elemental name
	FName ElementalName;
	ABaseCharacter* OwningCharacter = nullptr;
public:
	//Constructor
	Elemental();
	Elemental(ABaseCharacter* character);
	Elemental(const Elemental &other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	//Destructor
	virtual ~Elemental();
	//Overload = operator
	Elemental& operator=(const Elemental& other) {
		if (this == &other) return *this;
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
		return *this;
	}
	//Print test
	virtual void TestType() {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
		UE_LOG(LogTemp, Log, TEXT("%s"), *FString::Printf(TEXT("Element Type : %s"), *ElementalName.ToString()));
	};
	//Buff character after switching to this element
	virtual void ElementBuff() {};
	//Debuff character after switching to other element
	virtual void SwitchElementDebuff() {};
	FName GetName() { return ElementalName; }

};
class Fire :public Elemental {
public:
	Fire();
	Fire(ABaseCharacter* character) : Elemental(character) { Fire(); }
	Fire(const Fire& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Water :public Elemental {
public:
	Water();
	Water(ABaseCharacter* character) : Elemental(character) { Water(); }
	Water(const Water& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Earth : public Elemental {
public:
	Earth();
	Earth(ABaseCharacter* character) : Elemental(character) { Earth(); }
	Earth(const Earth& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Metal : public Elemental {
public:
	Metal();
	Metal(ABaseCharacter* character) : Elemental(character) { Metal(); }
	Metal(const Metal& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};
class Plant : public Elemental {
public:
	Plant();
	Plant(ABaseCharacter* character) : Elemental(character) { Plant(); }
	Plant(const Plant& other) {
		Buff = other.Buff;
		ElementalName = other.ElementalName;
		OwningCharacter = other.OwningCharacter;
	}
	void ElementBuff() override;
	void SwitchElementDebuff() override;
};


