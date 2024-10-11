// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"

void UMainCharacterHUD::SetupHUD()
{
	if (this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			HUDSkillList = MainCharacter->GetSkillList();
			SetupSkillSlotBox(HUDSkillList);
			SetCoinText(FText::FromString(FString::FromInt(0)));
			ProgBar_HPBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetHealthPercentage"));
			ProgBar_ManaBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetManaPercentage"));
		}
	}
}


void UMainCharacterHUD::SetupSkillSlotBox(TSharedPtr<TArray<TSharedPtr<BaseSkill>>> list)
{
	if (this->SkillSlotSubClass) {
		for (int i = 0; i < list->Num(); ++i) {
			USkillSlot* skillSlot = CreateWidget<USkillSlot>(this, this->SkillSlotSubClass);
			if (skillSlot) {
				TSharedPtr<BaseSkill> CurSkill = (*list)[i];
				FText SkillName = FText::FromString(CurSkill->GetName().ToString());
				skillSlot->GetIcon()->SetBrushResourceObject(Cast<UObject>(CurSkill->GetSkillSprite()));
				skillSlot->SetSkillNameText(SkillName);
				if (i != 0) {
					FMargin SlotMargin(0.0f, 5.0f, 0.0f, 0.0f);
					skillSlot->SetPadding(SlotMargin);
				}
				VerBox_SkillSlotBox->AddChildToVerticalBox(skillSlot);
			}
		}
	}
}

void UMainCharacterHUD::SwitchedSlotHighlight(int SwitchedNodeId)
{
	TArray<UWidget*> slotArr = VerBox_SkillSlotBox->GetAllChildren();
	if (slotArr.Num() > 0) {
		for (int i = 0; i < slotArr.Num(); ++i) {
			if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[i])) {
				skillSlot->HideOutline();
			}
		}
	}
	for (int i = 0; i < HUDSkillList->Num(); ++i) {
		if (i == SwitchedNodeId) {
			if (USkillSlot* slot = Cast<USkillSlot>(VerBox_SkillSlotBox->GetChildAt(i))) {
				slot->ShowOutline();
				break;
			}
		}
	}
}

void UMainCharacterHUD::RefreshSkillSlots(TSharedPtr<TArray<TSharedPtr<BaseSkill>>> skillList)
{
	HUDSkillList = skillList;
	if (VerBox_SkillSlotBox->HasAnyChildren()) {
		VerBox_SkillSlotBox->ClearChildren();
		SetupSkillSlotBox(HUDSkillList);
		SwitchedSlotHighlight(0);
	}
}
