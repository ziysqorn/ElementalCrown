// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"
#include "ManaPotion.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UManaPotion : public UConsumable
{

	GENERATED_BODY()

protected:
	int ManaAmount = 10;

public:
	UManaPotion();

	bool Consume() override;
};
