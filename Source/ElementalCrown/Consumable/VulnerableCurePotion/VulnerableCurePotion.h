// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"
#include "VulnerableCurePotion.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UVulnerableCurePotion : public UConsumable
{
	GENERATED_BODY()
	
public:
	UVulnerableCurePotion();
	bool Consume() override;
};
