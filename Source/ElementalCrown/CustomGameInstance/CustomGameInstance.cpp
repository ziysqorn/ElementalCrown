// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "../Controller/MainController.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../CustomSave/GameSettingSave.h"

void UCustomGameInstance::Init()
{
	Super::Init();


	GetWorld()->GetTimerManager().SetTimer(SetSoundMixHandle, FTimerDelegate::CreateUObject(this, &UCustomGameInstance::LoadSoundSetting), 1.0f, false);
}

void UCustomGameInstance::SpawnLoadingScreen()
{
	if (LoadingScreenSubclass) {
		if (!LoadingScreen) {
			LoadingScreen = CreateWidget<ULoadingScreen>(this, LoadingScreenSubclass);
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnim();
		}
		else {
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnim();
		}
	}
}

void UCustomGameInstance::SpawnReverseLoadingScreen()
{
	if (LoadingScreenSubclass) {
		if (!LoadingScreen) {
			LoadingScreen = CreateWidget<ULoadingScreen>(this, LoadingScreenSubclass);
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnimReverse();
		}
		else {
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnimReverse();
		}
	}
}

void UCustomGameInstance::SpawnFlashScreen()
{
	if (FlashScreenSubclass) {
		if (!FlashScreen) {
			FlashScreen = CreateWidget<ULoadingScreen>(this, FlashScreenSubclass);
			FlashScreen->AddToViewport(20);
			FlashScreen->PlayFadeinAnim();
		}
		else {
			FlashScreen->AddToViewport(20);
			FlashScreen->PlayFadeinAnim();
		}
	}
}

void UCustomGameInstance::SpawnReverseFlashScreen()
{
	if (FlashScreenSubclass) {
		if (!FlashScreen) {
			FlashScreen = CreateWidget<ULoadingScreen>(this, FlashScreenSubclass);
			FlashScreen->AddToViewport(20);
			FlashScreen->PlayFadeinAnimReverse();
		}
		else {
			FlashScreen->AddToViewport(20);
			FlashScreen->PlayFadeinAnimReverse();
		}
	}
}

void UCustomGameInstance::OpenLevel(FName LevelName)
{
	GetWorld()->GetTimerManager().SetTimer(SwitchLevelHandle, FTimerDelegate::CreateUObject(this, &UCustomGameInstance::OpenLevelImmediate, LevelName), 1.0f, false);
}

void UCustomGameInstance::OpenLevelAfterFlash(FName LevelName)
{
	GetWorld()->GetTimerManager().SetTimer(SwitchLevelHandle, FTimerDelegate::CreateUObject(this, &UCustomGameInstance::OpenLevelImmediate, LevelName), 1.5f, false);
}

void UCustomGameInstance::OpenLevelImmediate(FName LevelName)
{
	UGameplayStatics::OpenLevel(this, LevelName);
}

void UCustomGameInstance::PlayBattleTheme()
{
	if (BattleTheme) {
		if (BackgroundThemeManager && BackgroundThemeManager->IsPlaying()) BackgroundThemeManager->FadeOut(1.0f, 0.0f);
		BattleThemeManager = UGameplayStatics::SpawnSound2D(this, BattleTheme);
	}
}

void UCustomGameInstance::PlayBackgroundTheme(USoundBase* BackgroundTheme)
{
	if (BackgroundTheme) {
		if (BattleThemeManager && BattleThemeManager->IsPlaying()) BattleThemeManager->FadeOut(1.0f, 0.0f);
		BackgroundThemeManager = UGameplayStatics::SpawnSound2D(this, BackgroundTheme);
	}
}

void UCustomGameInstance::FadeoutBattleTheme()
{
	if (BattleThemeManager) {
		BattleThemeManager->FadeOut(1.5f, 0.0f);
	}
}

void UCustomGameInstance::PlayBossDefeatSFX()
{
	if (BossDefeatSFX) UGameplayStatics::PlaySound2D(this, BossDefeatSFX);
}

void UCustomGameInstance::ApplySoundSetting(float MusicVolume, float SFXVolume)
{
	UGameplayStatics::SetSoundMixClassOverride(this, OverallGameSoundMix, MusicClass, MusicVolume, 1.0f, 0.0f);
	UGameplayStatics::SetSoundMixClassOverride(this, OverallGameSoundMix, SFXClass, SFXVolume, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(this, OverallGameSoundMix);
}

void UCustomGameInstance::LoadSoundSetting()
{
	if (UGameplayStatics::DoesSaveGameExist("GameSetting", 0)) {
		if (UGameSettingSave* GameSetting = Cast<UGameSettingSave>(UGameplayStatics::LoadGameFromSlot("GameSetting", 0))) {
			ApplySoundSetting(*GameSetting->GetSavedMusicVolume(), *GameSetting->GetSavedSFXVolume());
		}
	}
	else {
		if (UGameSettingSave* GameSetting = Cast<UGameSettingSave>(UGameplayStatics::CreateSaveGameObject(UGameSettingSave::StaticClass()))) {
			float* SavedMusicVolume = GameSetting->GetSavedMusicVolume();
			float* SavedSFXVolume = GameSetting->GetSavedSFXVolume();
			*SavedMusicVolume = 1.0f;
			*SavedSFXVolume = 1.0f;
			ApplySoundSetting(*SavedMusicVolume, *SavedSFXVolume);
			UGameplayStatics::SaveGameToSlot(GameSetting, "GameSetting", 0);
		}
	}
}

