// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "ShopData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct ELEMENTALCROWN_API FShopData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObject> DataClass;

public:
	FShopData();
};
