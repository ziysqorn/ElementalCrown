// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Stun.h"

/**
 *
 */

class ELEMENTALCROWN_API StunStatus : public BaseStatusEffect
{
protected:
	AStun* StunEffect = nullptr;
	float TimeElapsed = 0.0f;
	float BuildupToFill = 10.0f;
	float CurrentProgress = 0.0f;
	bool isActivated = false;
public:
	StunStatus();
	~StunStatus() override;
	bool GetActivateStatus() { return isActivated; }
	void BuildingUp(const float& inBuildup);
	void ExecuteStatus() override;
};
