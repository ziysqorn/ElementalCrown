// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "PaperSprite.h"
#include "PaperFlipbook.h"
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
	UTextBlock* SkillName = nullptr;
public:
	UImage* GetIcon() { return SkillIcon; }
	void ShowOutline() {
		if (SkillOutline) SkillOutline->SetVisibility(ESlateVisibility::Visible);
	}
	void HideOutline() {
		if (SkillOutline) SkillOutline->SetVisibility(ESlateVisibility::Hidden);
	}
	void SetSkillNameText(FText inText) {
		SkillName->SetText(inText);
	}
};
