// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Drowsy.h"
#include "DrowsyStatus.generated.h"


/**
 *
 */

UCLASS()
class ELEMENTALCROWN_API UDrowsyStatus : public UBaseStatusEffect
{
	GENERATED_BODY()

public:
	UDrowsyStatus();
	void BeginDestroy() override;
	void ExecuteStatus() override;
};