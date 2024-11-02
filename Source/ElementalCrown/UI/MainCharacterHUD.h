// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../GameplayElemental/Elemental.h"
#include "../Skill/BaseSkill.h"
#include "../StatusEffect/BaseStatusEffect.h"
#include "../UI/Skill/SkillSlot.h"
#include "../UI/StatusEffectProgressUI/StatusEffectProgressUI.h"
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
	TSharedPtr<TArray<TSharedPtr<BaseSkill>>> HUDSkillList;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UHorizontalBox* HorBox_SkillSlotBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UTextBlock* Txt_Coin = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UProgressBar* ProgBar_HPBar = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UProgressBar* ProgBar_ManaBar = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UTextBlock* Txt_SkillName = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UVerticalBox* VerBox_StatusProgress = nullptr;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Slot SubClass")
	TSubclassOf<USkillSlot> SkillSlotSubClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status Effect Progress SubClass")
	TSubclassOf<UStatusEffectProgressUI> StatusEffectProgressSubClass;
	UHorizontalBox* GetSkillSlotBox() { return HorBox_SkillSlotBox; }
	UStatusEffectProgressUI* GetStatusProgressUI(const int& idx) {
		return Cast<UStatusEffectProgressUI>(VerBox_StatusProgress->GetChildAt(idx));
	}
	void SetupHUD();
	void SetupSkillSlotBox(TArray<TSharedPtr<BaseSkill>>* list);
	void SetCoinText(FText inText) {
		Txt_Coin->SetText(inText);
	};
	void SetSkillName(FText inText) {
		Txt_SkillName->SetText(inText);
	}
	void SetHPBar(float inPercent) {
		ProgBar_HPBar->SetPercent(inPercent);
	}
	void SetManaBar(float inPercent) {
		ProgBar_ManaBar->SetPercent(inPercent);
	}
	void UpdateSkillCountdownProgUI(BaseSkill* Skill, const float& inPercentage);
	void AddStatsEffectToVerBox(UUserWidget* StatsEffect);
	void RemoveStatsEffectFromVerBox(int removedIdx);
	void ShowSkillLoaderUI(BaseSkill* Skill);
	void HideSkillLoaderUI(BaseSkill* Skill);
	void SwitchedSlotHighlight(int SwitchedNodeId);
	void RefreshSkillSlots(TSharedPtr<TArray<TSharedPtr<BaseSkill>>> skillList);
};
