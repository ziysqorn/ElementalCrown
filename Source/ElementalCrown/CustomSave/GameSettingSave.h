// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "GameSettingSave.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UGameSettingSave : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	float MusicVolume;

	UPROPERTY()
	float SFXVolume;

public:
	float* GetSavedMusicVolume() {
		return &MusicVolume;
	}
	float* GetSavedSFXVolume() {
		return &SFXVolume;
	}
};
