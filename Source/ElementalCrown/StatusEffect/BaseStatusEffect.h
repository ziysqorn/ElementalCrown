// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Effects/StatusEffect/BaseStatus.h"
#include "BaseStatusEffect.generated.h"

/**
 * 
 */

class ABaseCharacter;

UCLASS()
class ELEMENTALCROWN_API UBaseStatusEffect : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FName StatusName;

	UPROPERTY()
	float TimeElapsed = 0.0f;

	UPROPERTY()
	float AffectingTime;

	UPROPERTY()
	ABaseStatus* StatusEffectActor = nullptr;

	UPROPERTY()
	ABaseCharacter* OwningCharacter = nullptr;

	UPROPERTY()
	ABaseCharacter* AffectedCharacter = nullptr;

	UPROPERTY()
	FTimerHandle EffectHandle;

	UPROPERTY()
	FTimerHandle ResetHandle;

	UPROPERTY()
	bool isActivated = false;

	UPROPERTY()
	float CurrentProgress = 0.0f;

	UPROPERTY()
	float BuildupToFill = 10.0f;

	UPROPERTY()
	float TimeForAReset;
public:
	UBaseStatusEffect();
	virtual void BeginDestroy() override;
	FName GetStatusName() { return StatusName; }
	bool GetActivateStatus() { return isActivated; }
	UFUNCTION()
	float GetBuildupPercentage() { return CurrentProgress / BuildupToFill; }
	UFUNCTION()
	float GetTimePercentage() { return (AffectingTime - TimeElapsed) / AffectingTime; }
	void SetOwningCharacter(ABaseCharacter* Character) {
		OwningCharacter = Character;
	}
	void SetAffectedCharacter(ABaseCharacter* Character) {
		AffectedCharacter = Character;
	}
	void RemoveStatusFromList();
	void RemoveStatusFromList(const int& idx);
	virtual void BuildingUp(const float& inBuildup);
	virtual void ExecuteStatus() {};
};
