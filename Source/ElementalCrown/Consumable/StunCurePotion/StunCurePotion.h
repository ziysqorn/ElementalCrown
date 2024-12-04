// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"
#include "StunCurePotion.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UStunCurePotion : public UConsumable
{
	GENERATED_BODY()
	
public:
	UStunCurePotion();
	bool Consume() override;
};
