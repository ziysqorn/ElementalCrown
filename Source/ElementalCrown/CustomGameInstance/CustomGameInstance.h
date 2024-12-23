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

	UPROPERTY()
	ULoadingScreen* FlashScreen = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Loading Screen")
	TSubclassOf<ULoadingScreen> LoadingScreenSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Black Flash Screen")
	TSubclassOf<ULoadingScreen> FlashScreenSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | SFX | Boss Defeat SFX")
	USoundBase* BossDefeatSFX = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | SFX | Battle theme")
	USoundBase* BattleTheme = nullptr;

	UPROPERTY()
	UAudioComponent* BattleThemeManager = nullptr;

	UPROPERTY()
	UAudioComponent* BackgroundThemeManager = nullptr;


	FTimerHandle SwitchLevelHandle;

public:
	void SpawnLoadingScreen();
	void SpawnReverseLoadingScreen();
	void SpawnFlashScreen();
	void SpawnReverseFlashScreen();
	void OpenLevel(FName LevelName);
	void OpenLevelAfterFlash(FName LevelName);
	void PlayBattleTheme();
	void PlayBackgroundTheme(USoundBase* BackgroundTheme);
	void FadeoutBattleTheme();
	void PlayBossDefeatSFX();
	ULoadingScreen* GetLoadingScreen() {
		return LoadingScreen;
	}

	ULoadingScreen* GetFlashScreen() {
		return FlashScreen;
	}

};
