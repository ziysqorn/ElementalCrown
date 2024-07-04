// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"

void UMainCharacterHUD::SetupHUD()
{
	if (this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			HUDElementalList = MainCharacter->GetElementalList();
			HUDSkillList = MainCharacter->GetSkillList();
			SetupElementalSlotBox(HUDElementalList);
			SetupSkillSlotBox(HUDSkillList);
			SetCoinText(FText::FromString(FString::FromInt(0)));
			ProgBar_HPBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetHealthPercentage"));
			ProgBar_ManaBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetManaPercentage"));
		}
	}
}

void UMainCharacterHUD::SetupElementalSlotBox(TSharedPtr<CustomLinkedList<Elemental>> list)
{
	if (this->ElementalSlotSubClass) {
		for (CustomNode<Elemental>* ptr = list->GetHead(); ptr != nullptr; ptr = ptr->next) {
			UElementalSlot* elementalSlot = CreateWidget<UElementalSlot>(this, this->ElementalSlotSubClass);
			if (elementalSlot) {
				elementalSlot->GetIcon()->SetBrushResourceObject(Cast<UObject>(elementalSlot->GetElementalSprite(ptr->GetValue()->GetName())));
				ElementalSlotBox->AddChildToHorizontalBox(elementalSlot);
			}
		}
	}
}

void UMainCharacterHUD::SetupSkillSlotBox(TSharedPtr<CustomLinkedList<BaseSkill>> list)
{
	if (this->SkillSlotSubClass) {
		for (CustomNode<BaseSkill>* ptr = list->GetHead(); ptr != nullptr; ptr = ptr->next) {
			USkillSlot* skillSlot = CreateWidget<USkillSlot>(this, this->SkillSlotSubClass);
			if (skillSlot) {
				FText SkillName = FText::FromString(ptr->GetValue()->GetName().ToString());
				skillSlot->GetIcon()->SetBrushResourceObject(Cast<UObject>(ptr->GetValue()->GetSkillSprite()));
				skillSlot->SetSkillNameText(SkillName);
				if (ptr != HUDSkillList->GetHead()) {
					FMargin SlotMargin(0.0f, 5.0f, 0.0f, 0.0f);
					skillSlot->SetPadding(SlotMargin);
				}
				VerBox_SkillSlotBox->AddChildToVerticalBox(skillSlot);
			}
		}
	}
}


void UMainCharacterHUD::SwitchedSlotHighlight(CustomNode<Elemental>* SwitchedNode)
{
	TArray<UWidget*> slotArr = ElementalSlotBox->GetAllChildren();
	if (slotArr.Num() > 0) {
		for (int i = 0; i < slotArr.Num(); ++i) {
			if (UElementalSlot* elementalSlot = Cast<UElementalSlot>(slotArr[i])) {
				elementalSlot->HideOutline();
			}
		}
	}
	int index = 0;
	for (CustomNode<Elemental>* ptr = HUDElementalList->GetHead(); ptr != nullptr; ptr = ptr->next) {
		if (ptr->GetValue()->GetName() == SwitchedNode->GetValue()->GetName()) {
			if (UElementalSlot* slot = Cast<UElementalSlot>(ElementalSlotBox->GetChildAt(index))) {
				slot->ShowOutline();
				break;
			}
		}
		++index;
	}
}

void UMainCharacterHUD::SwitchedSlotHighlight(CustomNode<BaseSkill>* SwitchedNode)
{
	TArray<UWidget*> slotArr = VerBox_SkillSlotBox->GetAllChildren();
	if (slotArr.Num() > 0) {
		for (int i = 0; i < slotArr.Num(); ++i) {
			if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[i])) {
				skillSlot->HideOutline();
			}
		}
	}
	int index = 0;
	for (CustomNode<BaseSkill>* ptr = HUDSkillList->GetHead(); ptr != nullptr; ptr = ptr->next) {
		if (ptr->GetValue() == SwitchedNode->GetValue()) {
			if (USkillSlot* slot = Cast<USkillSlot>(VerBox_SkillSlotBox->GetChildAt(index))) {
				slot->ShowOutline();
				break;
			}
		}
		++index;
	}
}

void UMainCharacterHUD::RefreshSkillSlots(TSharedPtr<CustomLinkedList<BaseSkill>> skillList)
{
	HUDSkillList = skillList;
	if (VerBox_SkillSlotBox->HasAnyChildren()) {
		VerBox_SkillSlotBox->ClearChildren();
		SetupSkillSlotBox(HUDSkillList);
		SwitchedSlotHighlight(HUDSkillList->GetHead());
	}
}
