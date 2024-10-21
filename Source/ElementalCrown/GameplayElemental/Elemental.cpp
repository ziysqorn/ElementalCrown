// Fill out your copyright notice in the Description page of Project Settings.


#include "Elemental.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

Elemental::Elemental()
{
}


Elemental::~Elemental()
{
}

Fire::Fire()
{
	ElementalName = "Fire";
	ApplyEffectChanceRange = 4;
}

void Fire::ApplyStatusEffect(ABaseCharacter* AffectedCharacter)
{
	if (AffectedCharacter) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			TSharedPtr<BaseStatusEffect> value = (*CurEffectList)[i];
			if (value.IsValid() && value->GetStatusName().IsEqual("Burn")) return;
		}
		/*if (FMath::RandRange(1, ApplyEffectChanceRange) == 1) {
		}*/
		TSharedPtr<BaseStatusEffect> newStatus = MakeShared<BurnStatus>();
		CurEffectList->Add(newStatus);
		newStatus->SetOwningCharacter(OwningCharacter);
		newStatus->SetAffectedCharacter(AffectedCharacter);
		newStatus->ExecuteStatus();
	}
}

Water::Water()
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


Metal::Metal()
{
	ElementalName = "Metal";
	ApplyEffectChanceRange = 5;
}

void Metal::ApplyStatusEffect(ABaseCharacter* AffectedCharacter)
{
	if (AffectedCharacter) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			TSharedPtr<BaseStatusEffect> value = (*CurEffectList)[i];
			if (value.IsValid() && value->GetStatusName().IsEqual("Bleed")) return;
		}
		if (FMath::RandRange(1, ApplyEffectChanceRange) == 1) {
			TSharedPtr<BaseStatusEffect> newStatus = MakeShared<BleedStatus>();
			CurEffectList->Add(newStatus);
			newStatus->SetOwningCharacter(OwningCharacter);
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->ExecuteStatus();
		}
	}
}

Plant::Plant()
{
	ElementalName = "Plant";
}
