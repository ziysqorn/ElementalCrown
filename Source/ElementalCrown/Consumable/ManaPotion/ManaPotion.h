// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Consumable.h"

/**
 * 
 */
class ELEMENTALCROWN_API ManaPotion : public Consumable
{

protected:
	int ManaAmount = 20;

public:
	ManaPotion();
	~ManaPotion();

	void Consume() override;
};