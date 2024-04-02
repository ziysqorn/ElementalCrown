// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Characters/Main Character/MainCharacter.h"
#include "CoreMinimal.h"

/**
 * 
 */
class AMainCharacter;
class ELEMENTALCROWN_API Elemental
{
public:
	int Buff{0};
	//Constructor
	Elemental();
	//Destructor
	virtual ~Elemental();
	//Print test
	virtual void TestType() {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Element Type : None"));
	};
	//Buff character after switching to this element
	virtual void ElementBuff(AMainCharacter* MainCharacter) {};
	//Debuff character after switching to other element
	virtual void SwitchElementDebuff(AMainCharacter* MainCharacter) {};
};
class Fire :public Elemental {
public:
	Fire();
	void TestType() override {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Element Type : Fire"));
	};
	void ElementBuff(AMainCharacter* MainCharacter) override;
	void SwitchElementDebuff(AMainCharacter* MainCharacter) override;
};
class Water :public Elemental {
public:
	Water();
	void TestType() override {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Element Type : Water"));
	};
	void ElementBuff(AMainCharacter* MainCharacter) override;
	void SwitchElementDebuff(AMainCharacter* MainCharacter) override;
};
class Earth : public Elemental {
public:
	Earth();
	void TestType() override {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Element Type : Earth"));
	};
	void ElementBuff(AMainCharacter* MainCharacter) override;
	void SwitchElementDebuff(AMainCharacter* MainCharacter) override;
};
class Metal : public Elemental {
public:
	Metal();
	void TestType() override {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Element Type : Metal"));
	};
	void ElementBuff(AMainCharacter* MainCharacter) override;
	void SwitchElementDebuff(AMainCharacter* MainCharacter) override;
};
class Plant : public Elemental {
public:
	Plant();
	void TestType() override {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Element Type : Plant"));
	};
	void ElementBuff(AMainCharacter* MainCharacter) override;
	void SwitchElementDebuff(AMainCharacter* MainCharacter) override;
};