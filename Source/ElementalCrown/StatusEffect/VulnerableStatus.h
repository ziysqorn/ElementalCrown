// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Vulnerable.h"

/**
 *
 */

class ELEMENTALCROWN_API VulnerableStatus : public BaseStatusEffect
{
public:
	VulnerableStatus();
	void ExecuteStatus() override;
};