// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Stun.h"
#include "StunStatus.generated.h"

/**
 *
 */

UCLASS()
class ELEMENTALCROWN_API UStunStatus : public UBaseStatusEffect
{
	GENERATED_BODY()
public:
	UStunStatus();
	void BeginDestroy() override;
	void ExecuteStatus() override;
};
