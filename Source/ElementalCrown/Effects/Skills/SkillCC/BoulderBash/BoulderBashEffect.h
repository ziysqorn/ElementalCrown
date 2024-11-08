// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "BoulderBashEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ABoulderBashEffect : public ASkillCC
{
	GENERATED_BODY()
public:
	ABoulderBashEffect();
	void BeginPlay() override;
};
