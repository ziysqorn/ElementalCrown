// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "FirePillarEffect.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API AFirePillarEffect : public ASkillCC
{
	GENERATED_BODY()
public:
	AFirePillarEffect();
	void BeginPlay() override;
};
