// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionUI.h"
#include "../../CustomSave/GameSettingSave.h"
#include "../../CustomGameInstance/CustomGameInstance.h"


void UOptionUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Slider_MusicVolume->OnValueChanged.AddDynamic(this, &UOptionUI::SetMusicVolume);
	Slider_SFXVolume->OnValueChanged.AddDynamic(this, &UOptionUI::SetSFXVolume);

	Btn_Close->OnClicked.AddDynamic(this, &UOptionUI::RemoveFromParent);

	Btn_ApplySoundSetting->OnClicked.AddDynamic(this, &UOptionUI::ApplySoundSetting);

	SetIsFocusable(true);
}

void UOptionUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGameSettingSave* GameSetting = Cast<UGameSettingSave>(UGameplayStatics::LoadGameFromSlot("GameSetting", 0))) {
		float* SavedMusicVolume = GameSetting->GetSavedMusicVolume();
		float* SavedSFXVolume = GameSetting->GetSavedSFXVolume();
		Slider_MusicVolume->SetValue(*SavedMusicVolume);
		Slider_SFXVolume->SetValue(*SavedSFXVolume);
	}
}

void UOptionUI::SetMusicVolume(float Volume)
{
	MusicVolume = Volume;
}

void UOptionUI::SetSFXVolume(float Volume)
{
	SFXVolume = Volume;
}

void UOptionUI::ApplySoundSetting()
{
	if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
		if (UGameSettingSave* GameSetting = Cast<UGameSettingSave>(UGameplayStatics::CreateSaveGameObject(UGameSettingSave::StaticClass()))) {
			float* SavedMusicVolume = GameSetting->GetSavedMusicVolume();
			float* SavedSFXVolume = GameSetting->GetSavedSFXVolume();
			*SavedMusicVolume = MusicVolume;
			*SavedSFXVolume = SFXVolume;
			CustomGameInstance->ApplySoundSetting(MusicVolume, SFXVolume);
			UGameplayStatics::SaveGameToSlot(GameSetting, "GameSetting", 0);
		}
	}
}
