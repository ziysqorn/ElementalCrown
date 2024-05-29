// Fill out your copyright notice in the Description page of Project Settings.


#include "MainController.h"

void AMainController::BeginPlay()
{
	Super::BeginPlay();
	if (MainHUBSubClass) {
		MainHUB = CreateWidget<UMainCharacterHUB>(this, MainHUBSubClass);
		SetupHUB();
		MainHUB->AddToViewport(0);
	}
}

void AMainController::SetupHUB()
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetPawn())) {
		ElementalList list;
		list = MainCharacter->GetElementalList();
		for (ElementalNode* ptr = list.GetHead(); ptr != nullptr; ptr = ptr->next) {
			if (MainHUB->ElementalSlotSubClass) {
				UElementalSlot* elementalSlot = CreateWidget<UElementalSlot>(this, MainHUB->ElementalSlotSubClass);
				if (elementalSlot) {
					elementalSlot->GetIcon()->SetBrushResourceObject(Cast<UObject>(elementalSlot->GetElementalSprite(ptr->GetValue()->GetName())));
					MainHUB->GetElementalSlotBox()->AddChildToHorizontalBox(elementalSlot);
				}
			}
		}
		MainHUB->SetOwningPlayer(this);
	}
}
