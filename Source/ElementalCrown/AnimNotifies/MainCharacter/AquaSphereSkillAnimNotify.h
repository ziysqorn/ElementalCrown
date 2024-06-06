// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableSkillAnimNotify.h"
#include "../../Effects/Skills/SkillProjectile/AquaSphereProjectile/AquaSphereProjectile.h"
#include "AquaSphereSkillAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UAquaSphereSkillAnimNotify : public USpawnableSkillAnimNotify
{
	GENERATED_BODY()
	
public:
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
