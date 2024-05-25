// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackAnimNotify.h"
#include "../../Effects/Impact/AttackImpact/PunchImpact.h"
#include "Punch1AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UPunch1AnimNotify : public UAttackAnimNotify
{
	GENERATED_BODY()
	
public:
	UPunch1AnimNotify();
	virtual void SetBuff() override;
	virtual void SpawnImpact(APaperZDCharacter* Character, const ECollisionChannel& OwnerObjectType, const FHitResult& Target) const override;
};
