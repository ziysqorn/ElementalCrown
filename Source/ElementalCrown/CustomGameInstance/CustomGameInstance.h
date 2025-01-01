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

	UPROPERTY(EditDefaultsOnly, Category = "Important | Music class")
	USoundClass* MusicClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | SFX class")
	USoundClass* SFXClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Overall Game Sound Mix")
	USoundMix* OverallGameSoundMix = nullptr;

	UPROPERTY()
	UAudioComponent* BattleThemeManager = nullptr;

	UPROPERTY()
	UAudioComponent* BackgroundThemeManager = nullptr;


	FTimerHandle SwitchLevelHandle;

	FTimerHandle SetSoundMixHandle;

public:
	void Init() override;

	void SpawnLoadingScreen();

	void SpawnReverseLoadingScreen();

	void SpawnFlashScreen();

	void SpawnReverseFlashScreen();

	void OpenLevel(FName LevelName);

	void OpenLevelAfterFlash(FName LevelName);

	void OpenLevelImmediate(FName LevelName);

	void PlayBattleTheme();

	void PlayBackgroundTheme(USoundBase* BackgroundTheme);

	void FadeoutBattleTheme();

	void PlayBossDefeatSFX();

	void ApplySoundSetting(float MusicVolume, float SFXVolume);

	void LoadSoundSetting();

	ULoadingScreen* GetLoadingScreen() {
		return LoadingScreen;
	}

	ULoadingScreen* GetFlashScreen() {
		return FlashScreen;
	}

};
