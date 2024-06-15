// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/GridPanel.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "Elemental/ElementalSlot.h"
#include "Skill/SkillSlot.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "MainCharacterHUD.generated.h"

/**
 * 
 */

UCLASS()
class ELEMENTALCROWN_API UMainCharacterHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	std::shared_ptr<CustomLinkedList<Elemental>> HUDElementalList;
	std::shared_ptr<CustomLinkedList<BaseSkill>> HUDSkillList;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UHorizontalBox* ElementalSlotBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UVerticalBox* VerBox_SkillSlotBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UTextBlock* Txt_Coin = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UProgressBar* ProgBar_HPBar = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UProgressBar* ProgBar_ManaBar = nullptr;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Elemental Slot SubClass")
	TSubclassOf<UElementalSlot> ElementalSlotSubClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Slot SubClass")
	TSubclassOf<USkillSlot> SkillSlotSubClass;
	UHorizontalBox* GetElementalSlotBox() { return ElementalSlotBox; }
	UVerticalBox* GetSkillSlotBox() { return VerBox_SkillSlotBox; }
	void SetupHUD();
	void SetupElementalSlotBox(std::shared_ptr<CustomLinkedList<Elemental>> list);
	void SetupSkillSlotBox(std::shared_ptr<CustomLinkedList<BaseSkill>> list);
	void SetCoinText(FText inText) {
		Txt_Coin->SetText(inText);
	};
	void SetHPBar(float inPercent) {
		ProgBar_HPBar->SetPercent(inPercent);
	}
	void SetManaBar(float inPercent) {
		ProgBar_ManaBar->SetPercent(inPercent);
	}
	void SwitchedSlotHighlight(CustomNode<Elemental>* SwitchedNode);
	void SwitchedSlotHighlight(CustomNode<BaseSkill>* SwitchedNode);
	void RefreshSkillSlots(std::shared_ptr<CustomLinkedList<BaseSkill>> skillList);
};
