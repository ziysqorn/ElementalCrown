// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"

void UMainCharacterHUD::SetupHUD()
{
	if (this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			HUDSkillList = MainCharacter->GetSkillList();
			SetupSkillSlotBox(HUDSkillList.Get());
			SetCoinText(FText::FromString(FString::FromInt(0)));
			ProgBar_HPBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetHealthPercentage"));
			ProgBar_ManaBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetManaPercentage"));
		}
	}
}


void UMainCharacterHUD::SetupSkillSlotBox(TArray<TSharedPtr<BaseSkill>>* list)
{
	if (this->SkillSlotSubClass) {
		for (int i = 0; i < list->Num(); ++i) {
			USkillSlot* skillSlot = CreateWidget<USkillSlot>(this, this->SkillSlotSubClass);
			if (skillSlot) {
				TSharedPtr<BaseSkill> CurSkill = (*list)[i];
				skillSlot->GetIcon()->SetBrushResourceObject(Cast<UObject>(CurSkill->GetSkillSprite()));
				if (i != 0) {
					FMargin SlotMargin(10.0f, 0.0f, 0.0f, 0.0f);
					skillSlot->SetPadding(SlotMargin);
				}
				skillSlot->UpdateCountdownProgress(0.0f);
				skillSlot->HideLoadBorder();
				HorBox_SkillSlotBox->AddChildToHorizontalBox(skillSlot);
			}
		}
	}
}

void UMainCharacterHUD::UpdateSkillCountdownProgUI(BaseSkill* Skill, const float& inPercentage)
{
	if (Skill) {
		TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
		if (slotArr.Num() > 0 && slotArr.Num() == HUDSkillList->Num()) {
			for (int i = 0; i < slotArr.Num(); ++i) {
				if ((*HUDSkillList)[i].Get() == Skill) {
					if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[i]))
						skillSlot->UpdateCountdownProgress(inPercentage);
				}
			}
		}
	}
}

void UMainCharacterHUD::AddStatsEffectToVerBox(UUserWidget* StatsEffect)
{
	VerBox_StatusProgress->AddChildToVerticalBox(StatsEffect);
}

void UMainCharacterHUD::RemoveStatsEffectFromVerBox(int removedIdx)
{
	VerBox_StatusProgress->RemoveChildAt(removedIdx);
}


void UMainCharacterHUD::ShowSkillLoaderUI(BaseSkill* Skill)
{
	if (Skill) {
		TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
		if (slotArr.Num() > 0 && slotArr.Num() == HUDSkillList->Num()) {
			for (int i = 0; i < slotArr.Num(); ++i) {
				if ((*HUDSkillList)[i].Get() == Skill) {
					if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[i])) skillSlot->ShowLoadBorder();
				}
			}
		}
	}
}

void UMainCharacterHUD::HideSkillLoaderUI(BaseSkill* Skill)
{
	if (Skill) {
		TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
		if (slotArr.Num() > 0 && slotArr.Num() == HUDSkillList->Num()) {
			for (int i = 0; i < slotArr.Num(); ++i) {
				if ((*HUDSkillList)[i].Get() == Skill) {
					if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[i])) {
						skillSlot->UpdateCountdownProgress(0.0f);
						skillSlot->HideLoadBorder();
					}
				}
			}
		}
	}
}

void UMainCharacterHUD::SwitchedSlotHighlight(int SwitchedNodeId)
{
	TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
	if (slotArr.Num() > 0 && slotArr.Num() == HUDSkillList->Num()) {
		for (int i = 0; i < slotArr.Num(); ++i) {
			if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[i])) {
				skillSlot->HideOutline();
			}
		}
	}
	for (int i = 0; i < HUDSkillList->Num(); ++i) {
		if (i == SwitchedNodeId) {
			if (USkillSlot* slot = Cast<USkillSlot>(HorBox_SkillSlotBox->GetChildAt(i))) {
				slot->ShowOutline();
				FString SkillName = (*HUDSkillList)[i]->GetName().ToString();
				Txt_SkillName->SetText(FText::FromString(SkillName));
				break;
			}
		}
	}
}

void UMainCharacterHUD::RefreshSkillSlots(TSharedPtr<TArray<TSharedPtr<BaseSkill>>> skillList)
{
	HUDSkillList = skillList;
	if (HorBox_SkillSlotBox->HasAnyChildren()) {
		HorBox_SkillSlotBox->ClearChildren();
		SetupSkillSlotBox(HUDSkillList.Get());
		SwitchedSlotHighlight(0);
	}
}
