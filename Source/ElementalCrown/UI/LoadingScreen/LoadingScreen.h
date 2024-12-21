// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "LoadingScreen.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FLoadingScreenEndDel)

UCLASS()
class ELEMENTALCROWN_API ULoadingScreen : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;
	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeinBackground = nullptr;

	FTimerHandle LoadTimeHandle;

	FTimerHandle FadeAwayEndHandle;

	UFUNCTION()
	void PlayReverseImmediate();

	UFUNCTION()
	void LoadEndAction();

public:
	FLoadingScreenEndDel LoadingScreenEndDel;

	void PlayFadeinAnim();

	void PlayFadeinAnimReverse();
};
