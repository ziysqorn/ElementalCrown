// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "PoseidonAuraEffect.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API APoseidonAuraEffect : public ASkillCC
{
	GENERATED_BODY()
public:
	APoseidonAuraEffect();
	void BeginPlay() override;
};
