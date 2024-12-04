// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Skill/BaseSkill.h"
#include "SkillData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct ELEMENTALCROWN_API FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseSkill> DataClass;
};
