// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Drowsy.h"

/**
 *
 */

class ELEMENTALCROWN_API DrowsyStatus : public BaseStatusEffect
{
protected:
	ADrowsy* DrowsyEffect = nullptr;
	float BuildupToFill = 10.0f;
	float CurrentProgress = 0.0f;
	bool isActivated = false;
public:
	DrowsyStatus();
	~DrowsyStatus() override;
	bool GetActivateStatus() { return isActivated; }
	void BuildingUp(const float& inBuildup);
	void ExecuteStatus() override;
};