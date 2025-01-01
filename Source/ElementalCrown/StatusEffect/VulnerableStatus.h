// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Vulnerable.h"
#include "VulnerableStatus.generated.h"

/**
 *
 */

UCLASS()
class ELEMENTALCROWN_API UVulnerableStatus : public UBaseStatusEffect
{
	GENERATED_BODY()

public:
	UVulnerableStatus();
	void ExecuteStatus() override;
};