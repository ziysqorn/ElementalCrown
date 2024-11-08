// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "../../../Explode/StoneBarrage/StoneBarrageExplode.h"
#include "StoneBarrageEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AStoneBarrageEffect : public ASkillProjectile
{
	GENERATED_BODY()
public:
	AStoneBarrageEffect();
	void SpawnExplosion() override;
};
