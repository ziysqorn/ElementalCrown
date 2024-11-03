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
public:
	StunStatus();
	~StunStatus() override;
	void ExecuteStatus() override;
};
