// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../UI/LoadingScreen/LoadingScreen.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	ULoadingScreen* LoadingScreen = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Loading Screen")
	TSubclassOf<ULoadingScreen> LoadingScreenSubclass;

	FTimerHandle SwitchLevelHandle;

public:
	void SpawnLoadingScreen();
	void SpawnReverseLoadingScreen();
	void OpenLevel(FName LevelName);
	ULoadingScreen* GetLoadingScreen() {
		return LoadingScreen;
	}

};
