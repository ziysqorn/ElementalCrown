// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "ScreenMessage.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UScreenMessage : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;

	void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* Txt_Message = nullptr;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* Fadein = nullptr;

	UFUNCTION()
	virtual void AnimEndAction();
public:
	void PlayFadein();
};
