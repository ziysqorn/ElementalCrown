// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"
#include "BurnCurePotion.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UBurnCurePotion : public UConsumable
{
	GENERATED_BODY()
	
public:
	UBurnCurePotion();
	bool Consume() override;
};
