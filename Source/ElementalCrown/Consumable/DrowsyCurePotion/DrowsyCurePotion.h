// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"
#include "DrowsyCurePotion.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UDrowsyCurePotion : public UConsumable
{
	GENERATED_BODY()
	
public:
	UDrowsyCurePotion();
	bool Consume() override;
};
