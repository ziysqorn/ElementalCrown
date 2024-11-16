// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffect.h"
#include "../../../Characters/BaseCharacter/BaseCharacter.h"
#include "DmgOvertimeSkillEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ADmgOvertimeSkillEffect : public ASkillEffect
{
	GENERATED_BODY()

protected:
	float DelayTillCount = 0.0f;
	float TimePerHit = 0.0f;
	FTimerHandle DamageHandle;

public:
	ADmgOvertimeSkillEffect();

	ADmgOvertimeSkillEffect(const TCHAR* Ref);

	virtual void BeginPlay() override;

	virtual void ExecuteOverlap();
};
