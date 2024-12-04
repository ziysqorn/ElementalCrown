// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "GameplaySave.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UGameplaySave : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TArray<FName> OwnedSkills;

	UPROPERTY()
	TArray<int> EquippedSkillIdxList;

	UPROPERTY()
	TArray<FName> ConsumableList;

	UPROPERTY()
	TArray<int> ConsumableQuantList;

public:
	TArray<FName>& GetOwnedSkills() {
		return OwnedSkills;
	}

	TArray<int>& GetEquippedSkillIdxList() {
		return EquippedSkillIdxList;
	}

	TArray<FName>& GetConsumableList() {
		return ConsumableList;
	}

	TArray<int>& GetConsumableQuantList() {
		return ConsumableQuantList;
	}
};
