// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MainCharacter/AttackAnimNotify.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "TimerManager.h"
#include "C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\Marketplace\PaperZD\Source\PaperZD\Public\AnimSequences\Players\PaperZDAnimPlayer.h"
#include "SpawnableSkillAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API USpawnableSkillAnimNotify : public UAttackAnimNotify
{
	GENERATED_BODY()
protected:
	mutable FVector SpawnLocation = FVector(0, 0, 0);
    mutable FRotator SpawnRotation = FRotator(0, 0, 0);
	mutable float SpawnDistanceX = 0.0f;
	//Done using this skill
	mutable FTimerHandle FinishSkill;
public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	void SetSpawnProperty(UPaperZDAnimInstance* OwningInstance);
};
