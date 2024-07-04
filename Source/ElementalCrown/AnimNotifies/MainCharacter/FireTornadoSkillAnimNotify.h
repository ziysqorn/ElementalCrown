// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableSkillAnimNotify.h"
#include "../../Effects/Skills/SkillProjectile/FireTornado/FireTornadoProjectile.h"
#include "FireTornadoSkillAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UFireTornadoSkillAnimNotify : public USpawnableSkillAnimNotify
{
	GENERATED_BODY()
public:
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
