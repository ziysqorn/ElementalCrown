// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DmgOvertimeSkillEffect.h"
#include "PoseidonAuraEffect.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API APoseidonAuraEffect : public ADmgOvertimeSkillEffect
{
	GENERATED_BODY()
public:
	APoseidonAuraEffect();

	void BeginPlay() override;

	void ExecuteOverlap() override;

	void DamageOvertime() override;
};
