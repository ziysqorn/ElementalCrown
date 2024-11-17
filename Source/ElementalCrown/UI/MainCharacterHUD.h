// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Skill/BaseSkill.h"
#include "../UI/Skill/SkillSlot.h"
#include "../UI/BossHealthBar/BossHealthBar.h"
#include "../UI/StatusEffectProgressUI/StatusEffectProgressUI.h"
#include "../UI/Consumable/ConsumableSlot.h"
#include "MainCharacterHUD.generated.h"

/**
 * 
 */

UCLASS()
class ELEMENTALCROWN_API UMainCharacterHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
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

	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	USizeBox* SizeBox_BossHealthbarBox = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UConsumableSlot* HealPotionSlot = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UConsumableSlot* MPPotionSlot = nullptr;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Slot SubClass")
	TSubclassOf<USkillSlot> SkillSlotSubClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss Healthbar SubClass")
	TSubclassOf<UBossHealthBar> BossHealthbarSubclass;
	UHorizontalBox* GetSkillSlotBox() { return HorBox_SkillSlotBox; }
	UConsumableSlot* GetConsumableSlot(const int& Type) {
		switch (Type) {
		case 1:
			return HealPotionSlot;
			break;
		case 2:
			return MPPotionSlot;
			break;
		}
		return nullptr;
	}
	UStatusEffectProgressUI* GetStatusProgressUI(const int& idx) {
		return Cast<UStatusEffectProgressUI>(VerBox_StatusProgress->GetChildAt(idx));
	}
	void SetupHUD();
	void SetupSkillSlotBox(TArray<BaseSkill*>& list);
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
	void AddStatsEffectToVerBox(UUserWidget* StatsEffect);
	void RemoveStatsEffectFromVerBox(int removedIdx);
	void UpdateSkillCountdownProgUI(BaseSkill* Skill, const float& inPercentage);
	void ShowSkillLoaderUI(BaseSkill* Skill);
	void HideSkillLoaderUI(BaseSkill* Skill);
	void SwitchedSlotHighlight(int SwitchedNodeId);
	void RefreshSkillSlots(TArray<BaseSkill*>& list);
	UBossHealthBar* AddBossHealthbarToBox();
	void RemoveBossHealthbarFromBox();
};
