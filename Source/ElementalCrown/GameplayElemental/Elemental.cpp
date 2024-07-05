// Fill out your copyright notice in the Description page of Project Settings.


#include "Elemental.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

Elemental::Elemental()
{
}

Elemental::Elemental(ABaseCharacter* character)
{
	OwningCharacter = character;
}

Elemental::~Elemental()
{
}

Fire::Fire()
{
	ElementalName = "Fire";
}

Fire::Fire(ABaseCharacter* character) : Elemental(character)
{
	ElementalName = "Fire";
}

void Fire::ApplyStatusEffect(ABaseCharacter* AffectedCharacter)
{
	TSharedPtr<CustomLinkedList<BaseStatusEffect>> CurEffectList = AffectedCharacter->GetStatusList();
	CustomNode<BaseStatusEffect>* prev = nullptr;
	for (CustomNode<BaseStatusEffect>* ptr = CurEffectList->GetHead(); ptr != nullptr; ptr = ptr->next) {
		if (BaseStatusEffect* value = ptr->GetValue()) {
			if (value->GetStatusName().IsEqual("Burn")) return;
		}
	}
	BaseStatusEffect* newStatus = new BurnStatus();
	CurEffectList->AddTail(new CustomNode<BaseStatusEffect>(newStatus));
	newStatus->SetOwningCharacter(OwningCharacter);
	newStatus->SetAffectedCharacter(AffectedCharacter);
	newStatus->ExecuteStatus();
}

Water::Water()
{
	ElementalName = "Water";
}

Water::Water(ABaseCharacter* character) : Elemental(character)
{
	ElementalName = "Water";
}

void Water::ApplyStatusEffect(ABaseCharacter* AffectedCharacter)
{
}

Earth::Earth()
{
	ElementalName = "Earth";
}

Earth::Earth(ABaseCharacter* character) : Elemental(character)
{
	ElementalName = "Earth";
}


Metal::Metal()
{
	ElementalName = "Metal";
}

Metal::Metal(ABaseCharacter* character) : Elemental(character)
{
	ElementalName = "Metal";
}

void Metal::ApplyStatusEffect(ABaseCharacter* AffectedCharacter)
{
	TSharedPtr<CustomLinkedList<BaseStatusEffect>> CurEffectList = AffectedCharacter->GetStatusList();
	for (CustomNode<BaseStatusEffect>* ptr = CurEffectList->GetHead(); ptr != nullptr; ptr = ptr->next) {
		if (BaseStatusEffect* value = ptr->GetValue()) {
			if (value->GetStatusName().IsEqual("Bleed")) return;
		}
	}
	BaseStatusEffect* newStatus = new BleedStatus();
	CurEffectList->AddTail(new CustomNode<BaseStatusEffect>(newStatus));
	newStatus->SetOwningCharacter(OwningCharacter);
	newStatus->SetAffectedCharacter(AffectedCharacter);
	newStatus->ExecuteStatus();
}

Plant::Plant()
{
	ElementalName = "Plant";
}

Plant::Plant(ABaseCharacter* character) : Elemental(character)
{
	ElementalName = "Plant";
}
