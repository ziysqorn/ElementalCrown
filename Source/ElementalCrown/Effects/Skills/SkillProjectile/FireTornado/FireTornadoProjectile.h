// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "../../../../Skill/EjectSkill/FireTornado/FireTornado.h"
#include "FireTornadoProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AFireTornadoProjectile : public ASkillProjectile
{
	GENERATED_BODY()
public:
	AFireTornadoProjectile();
	void BeginPlay() override;
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
