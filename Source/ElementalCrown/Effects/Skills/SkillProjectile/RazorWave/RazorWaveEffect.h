// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "../../../Explode/RazorWave/RazorWaveExplode.h"
#include "RazorWaveEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ARazorWaveEffect : public ASkillProjectile
{
	GENERATED_BODY()
public:
	//Constructor
	ARazorWaveEffect();
	void SpawnExplosion() override;
};
