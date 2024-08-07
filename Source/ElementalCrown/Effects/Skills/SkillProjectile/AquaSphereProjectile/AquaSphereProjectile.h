// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "../../../Explode/AquaSphereExplode/AquaSphereExplode.h"
#include "AquaSphereProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AAquaSphereProjectile : public ASkillProjectile
{
	GENERATED_BODY()
public:
	AAquaSphereProjectile();
	void BeginPlay() override;
	void SpawnExplosion() override;
	UFUNCTION()
	void SetLoopAtRightPos();
};
