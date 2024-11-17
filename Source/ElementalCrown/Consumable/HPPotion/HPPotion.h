// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"

/**
 * 
 */
class ELEMENTALCROWN_API HPPotion : public Consumable
{
protected:
	int HealAmount = 20;

public:
	HPPotion();
	~HPPotion();

	void Consume() override;
};
