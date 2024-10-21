// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Burn.h"

/**
 * 
 */

class ELEMENTALCROWN_API BurnStatus : public BaseStatusEffect
{
protected:
	int BurnDamage = 1;
	float TimeBetweenEachBurn = 0.75f;
	float TimeElapsed = 0.0f;
public:
	BurnStatus();
	~BurnStatus() override;
	void ExecuteStatus() override;
};
