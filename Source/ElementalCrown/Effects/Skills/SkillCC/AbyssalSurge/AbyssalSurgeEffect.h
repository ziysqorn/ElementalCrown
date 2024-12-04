// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "AbyssalSurgeEffect.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API AAbyssalSurgeEffect : public ASkillCCEffect
{
	GENERATED_BODY()
public:
	AAbyssalSurgeEffect();
	void BeginPlay() override;
};
