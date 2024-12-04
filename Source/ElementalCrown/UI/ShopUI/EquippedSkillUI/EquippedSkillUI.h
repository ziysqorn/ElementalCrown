// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../ProjectIncludes.h"
#include "../../../Skill/BaseSkill.h"
#include "EquippedSkillUI.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UEquippedSkillUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* Image_SkillAvt = nullptr;

	UBaseSkill* ManagedSkill = nullptr;

public:
	void SetItemImage(UPaperSprite* Image) {
		if (Image) Image_SkillAvt->SetBrushResourceObject(Image);
	}

	void SetItemImageVisible(ESlateVisibility inVisibility) {
		Image_SkillAvt->SetVisibility(inVisibility);
	}

	void SetManagedSkill(UBaseSkill* inSkill) {
		if (inSkill) ManagedSkill = inSkill;
	}
};
