// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "../../../Explode/LumberLaunch/LumberLaunchExplode.h"
#include "LumberLaunchEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ALumberLaunchEffect : public ASkillProjectile
{
	GENERATED_BODY()
public:
	ALumberLaunchEffect();
	void SpawnExplosion() override;
};
