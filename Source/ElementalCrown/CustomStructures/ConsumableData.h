// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Consumable/Consumable.h"
#include "ConsumableData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct ELEMENTALCROWN_API FConsumableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UConsumable> DataClass;
};
