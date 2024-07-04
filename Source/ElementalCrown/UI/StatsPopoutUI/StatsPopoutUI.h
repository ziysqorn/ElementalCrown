// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "StatsPopoutUI.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UStatsPopoutUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* StatsNumberText = nullptr;
public:
	void SetText(FText inText) {
		StatsNumberText->SetText(inText);
	}
	void SetTextColor(FLinearColor color) {
		FSlateColor newColor(color);
		StatsNumberText->SetColorAndOpacity(newColor);
	}
	void SetRenderOpacity(const float& inOpacity) {
		StatsNumberText->SetRenderOpacity(inOpacity);
	}
};
