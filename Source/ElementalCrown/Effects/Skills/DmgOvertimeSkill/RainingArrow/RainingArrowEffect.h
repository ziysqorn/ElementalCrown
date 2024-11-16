// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DmgOvertimeSkillEffect.h"
#include "RainingArrowEffect.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API ARainingArrowEffect : public ADmgOvertimeSkillEffect
{
	GENERATED_BODY()

public:
	ARainingArrowEffect();

	void BeginPlay() override;
};
