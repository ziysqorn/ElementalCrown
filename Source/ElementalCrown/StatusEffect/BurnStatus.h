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
	float TimeBetweenEachBurn = 0.5f;
public:
	BurnStatus();
	void ExecuteStatus() override;
};
