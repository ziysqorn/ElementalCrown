// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "GaleBurstEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AGaleBurstEffect : public ASkillCCEffect
{
	GENERATED_BODY()
public:
	AGaleBurstEffect();
	void BeginPlay() override;
};
