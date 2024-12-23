// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Skill/BaseSkill.h"
#include "../Consumable/Consumable.h"
#include "ShopSave.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UShopSave : public USaveGame
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<FName> SavedConsumables;

	UPROPERTY()
	TArray<FName> SavedAvailableSkills;

public:
	TArray<FName>& GetSavedConsumables() {
		return SavedConsumables;
	}

	TArray<FName>& GetSavedAvailableSkills() {
		return SavedAvailableSkills;
	}
};
