// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"
#include "Consumable.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UConsumable : public UObject
{

	GENERATED_BODY()

protected:
	FName ConsumableName;

	UPaperSprite* Avatar = nullptr;

	int Quantity = 0;

	int maxQuantity = 5;

	int ConsumablePrice;

public:
	UConsumable();
	UConsumable(const TCHAR* Ref);

	UPaperSprite* GetAvatar() {
		return Avatar;
	}

	FName& GetConsumableName() {
		return ConsumableName;
	}

	int* GetMaxQuant() {
		return &maxQuantity;
	}

	int* GetCurrentQuant() {
		return &Quantity;
	}

	int GetPrice() {
		return ConsumablePrice;
	}

	void SetConsumableName(FName Name) {
		ConsumableName = Name;
	}

	void SetQuantity(int quantity) {
		Quantity = quantity;
	}

	void SetMaxQuantity(int quantity) {
		maxQuantity = quantity;
	}

	void SetPrice(int price) {
		ConsumablePrice = price;
	}

	virtual bool Consume() { return false; };
};
