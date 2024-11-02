// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "StatusEffectProgressUI.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API UStatusEffectProgressUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Txt_StatusName = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* Img_StatusIcon = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* ProgBar_StatusEffectProg = nullptr;
public:
	UImage* GetIcon() {
		return Img_StatusIcon;
	}
	void SetStatusName(FText&& inText) {
		Txt_StatusName->SetText(inText);
	}
	UProgressBar* GetProgressBar() {
		return ProgBar_StatusEffectProg;
	}
};