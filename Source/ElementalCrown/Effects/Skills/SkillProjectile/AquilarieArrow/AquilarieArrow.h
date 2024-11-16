// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "AquilarieArrow.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AAquilarieArrow : public ASkillProjectile
{
	GENERATED_BODY()

public:
	AAquilarieArrow();
	void SpawnExplosion() override;
};
