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

	UPROPERTY(meta=(BindWidget))
	UBorder* Background = nullptr;

	FTimerHandle LoadTimeHandle;

	FTimerHandle FadeAwayEndHandle;

	UFUNCTION()
	void PlayReverseImmediate();

	UFUNCTION()
	void LoadEndAction();

public:
	FLoadingScreenEndDel LoadingScreenEndDel;

	void SetBackground(UObject* object) {
		if(Background && object){
			FSlateBrush BrushObject;
			BrushObject.SetResourceObject(object);
			Background->SetBrush(BrushObject);
		}
	}

	void SetBackgroundColor(FLinearColor color) {
		if (Background) {
			Background->SetBrushColor(color);
		}
	}

	void PlayFadeinAnim();

	void PlayFadeinAnimReverse();
};
