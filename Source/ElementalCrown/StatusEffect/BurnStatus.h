// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Burn.h"
#include "BurnStatus.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UBurnStatus : public UBaseStatusEffect
{
	GENERATED_BODY()

protected:
	int BurnDamage = 2;
	float TimeBetweenEachBurn = 0.5f;
public:
	UBurnStatus();
	void ExecuteStatus() override;
	void Burn();
};
