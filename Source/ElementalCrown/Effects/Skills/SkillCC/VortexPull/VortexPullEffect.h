// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "VortexPullEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AVortexPullEffect : public ASkillCCEffect
{
	GENERATED_BODY()
public:
	AVortexPullEffect();
	void BeginPlay() override;
};
