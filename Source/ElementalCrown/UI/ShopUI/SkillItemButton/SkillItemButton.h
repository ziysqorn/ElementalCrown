// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../ProjectIncludes.h"
#include "../../../Skill/BaseSkill.h"
#include "SkillItemButton.generated.h"

/**
 * 
 */
class UShopUI;

UCLASS()
class ELEMENTALCROWN_API USkillItemButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_ItemButton = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* Image_ItemAvt = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* Txt_ItemName = nullptr;

	UPROPERTY()
	UBaseSkill* ManagedSkill = nullptr;

	UPROPERTY()
	UShopUI* ParentShopUI = nullptr;

public:
	void SetManagedSkill(UBaseSkill* inSkill) {
		if (inSkill) ManagedSkill = inSkill;
	}
	void SetItemImage(UPaperSprite* Image) {
		if (Image) Image_ItemAvt->SetBrushResourceObject(Image);
	}

	void SetItemName(FText inText) {
		Txt_ItemName->SetText(inText);
	}

	void SetParentShopUI(UShopUI* inShopUI);

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
