// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "SkillSlot", meta = (BindWidget))
	UBorder* SkillFrame = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "SkillSlot", meta = (BindWidget))
	UBorder* SkillOutline = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "SkillSlot", meta = (BindWidget))
	UImage* SkillIcon = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "SkillSlot", meta = (BindWidget))
	UBorder* LoadBorder = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "SkillSlot", meta = (BindWidget))
	UImage* RoundProgressBar = nullptr;
public:
	UImage* GetIcon() { return SkillIcon; }
	void ShowOutline() {
		if (SkillOutline) SkillOutline->SetVisibility(ESlateVisibility::Visible);
	}
	void HideOutline() {
		if (SkillOutline) SkillOutline->SetVisibility(ESlateVisibility::Hidden);
	}
	void ShowLoadBorder() {
		if (LoadBorder) LoadBorder->SetVisibility(ESlateVisibility::Visible);
	}
	void HideLoadBorder() {
		if (LoadBorder) LoadBorder->SetVisibility(ESlateVisibility::Hidden);
	}
	void UpdateCountdownProgress(const float& inPercentage) {
		if (RoundProgressBar) {
			if (UMaterialInstanceDynamic* MaterialIns = RoundProgressBar->GetDynamicMaterial())
				MaterialIns->SetScalarParameterValue("Percentage", inPercentage);
		}
	}
};
