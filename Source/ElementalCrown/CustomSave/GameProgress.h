// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "GameProgress.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UGameProgress : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	FName LevelName;

	UPROPERTY()
	FVector PlayerLocation;

public:
	FName& GetLevelName() {
		return LevelName;
	}
	FVector& GetPlayerLocation() {
		return PlayerLocation;
	}
};
