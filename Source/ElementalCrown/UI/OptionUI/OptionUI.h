// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "OptionUI.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UOptionUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized();

	void NativeConstruct();

	float MusicVolume = 1.0f;

	float SFXVolume = 1.0f;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	USlider* Slider_MusicVolume = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	USlider* Slider_SFXVolume = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_ApplySoundSetting = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_Close = nullptr;

	UFUNCTION()
	void SetMusicVolume(float Volume);

	UFUNCTION()
	void SetSFXVolume(float Volume);

	UFUNCTION()
	void ApplySoundSetting();
};
