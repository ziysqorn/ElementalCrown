// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "EarthshatterUpliftEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AEarthshatterUpliftEffect : public ASkillCC
{
	GENERATED_BODY()
public:
	AEarthshatterUpliftEffect();
	void BeginPlay() override;
};
