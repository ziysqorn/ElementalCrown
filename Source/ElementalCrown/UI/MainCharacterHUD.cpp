// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"

void UMainCharacterHUD::SetupHUD()
{
	if (this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			HUDElementalList = MainCharacter->GetElementalList();
			for (CustomNode<Elemental>* ptr = HUDElementalList->GetHead(); ptr != nullptr; ptr = ptr->next) {
				if (this->ElementalSlotSubClass) {
					UElementalSlot* elementalSlot = CreateWidget<UElementalSlot>(this, this->ElementalSlotSubClass);
					if (elementalSlot) {
						elementalSlot->GetIcon()->SetBrushResourceObject(Cast<UObject>(elementalSlot->GetElementalSprite(ptr->GetValue()->GetName())));
						ElementalSlotBox->AddChildToHorizontalBox(elementalSlot);
					}
				}
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
