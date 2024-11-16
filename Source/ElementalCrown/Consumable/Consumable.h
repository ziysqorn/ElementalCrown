// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"

/**
 * 
 */
class ELEMENTALCROWN_API Consumable
{
protected:
	UPaperSprite* Avatar = nullptr;

	int Quantity = 0;

	int maxQuantity = 5;

public:
	Consumable();
	~Consumable();

	virtual void Consume() {};
};
