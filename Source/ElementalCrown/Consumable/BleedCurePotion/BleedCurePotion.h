// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"
#include "BleedCurePotion.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UBleedCurePotion : public UConsumable
{
	GENERATED_BODY()
	
public:
	UBleedCurePotion();
	bool Consume() override;
};
