// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

/**
 * 
 */
class ELEMENTALCROWN_API Consumable
{
protected:
	UPaperSprite* Avatar = nullptr;

	int Quantity = 3;

	int maxQuantity = 5;

	ABaseCharacter* OwningCharacter = nullptr;

public:
	Consumable();
	Consumable(const TCHAR* Ref);
	virtual ~Consumable();



	int* GetMaxQuant() {
		return &maxQuantity;
	}

	int* GetCurrentQuant() {
		return &Quantity;
	}

	void SetOwningChar(ABaseCharacter* BaseCharacter) {
		if (BaseCharacter) OwningCharacter = BaseCharacter;
	}

	virtual void Consume() {};
};
