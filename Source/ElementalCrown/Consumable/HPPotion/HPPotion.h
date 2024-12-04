// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"
#include "HPPotion.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UHPPotion : public UConsumable
{

	GENERATED_BODY()

protected:
	int HealAmount = 20;

public:
	UHPPotion();

	bool Consume() override;
};
