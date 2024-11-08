// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "RazorUprisingEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ARazorUprisingEffect : public ASkillCC
{
	GENERATED_BODY()
public:
	ARazorUprisingEffect();
	void BeginPlay() override;
};
