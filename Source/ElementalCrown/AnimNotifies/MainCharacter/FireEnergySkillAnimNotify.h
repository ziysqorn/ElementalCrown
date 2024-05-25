// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MainCharacter/SpawnableSkillAnimNotify.h"
#include "../../Effects/Skills/SkillProjectile/FireEnergyProjectile/FireEnergyProjectile.h"
#include "FireEnergySkillAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UFireEnergySkillAnimNotify : public USpawnableSkillAnimNotify
{
	GENERATED_BODY()
public:
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
