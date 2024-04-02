// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MainCharacter/AttackAnimNotify.h"
#include "SpawnableSkillAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API USpawnableSkillAnimNotify : public UAttackAnimNotify
{
	GENERATED_BODY()
protected:
	FVector SpawnLocation = FVector(0, 0, 0);
	FRotator SpawnRotation = FRotator(0, 0, 0);
	float SpawnDistanceX = 0.0f;
	//Done using this skill
	FTimerHandle FinishSkill;
public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) override {};
	void SetSpawnProperty(UPaperZDAnimInstance* OwningInstance);
};
