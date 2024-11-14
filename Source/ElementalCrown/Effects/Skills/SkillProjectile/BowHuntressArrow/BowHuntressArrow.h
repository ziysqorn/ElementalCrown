// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "BowHuntressArrow.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ABowHuntressArrow : public ASkillProjectile
{
	GENERATED_BODY()
	
public:
	ABowHuntressArrow();
	void SpawnExplosion() override;
};
