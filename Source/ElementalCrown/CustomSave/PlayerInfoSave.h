// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "PlayerInfoSave.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UPlayerInfoSave : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	FVector PlayerLocation;

	UPROPERTY()
	int PlayerHealth;

	UPROPERTY()
	int PlayerMana;

	UPROPERTY()
	int CurrentGold;

public:
	FVector& GetPlayerLocation() {
		return PlayerLocation;
	}

	int* GetPlayerHealth() {
		return &PlayerHealth;
	}

	int* GetPlayerMana() {
		return &PlayerMana;
	}

	int* GetCurrentGold() {
		return &CurrentGold;
	}
};
