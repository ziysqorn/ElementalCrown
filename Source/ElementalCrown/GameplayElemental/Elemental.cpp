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

void Earth::ApplyStunEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			TSharedPtr<BaseStatusEffect> value = (*CurEffectList)[i];
			if (value.IsValid() && value->GetStatusName().IsEqual("Drowsy")) {
				if (StunStatus* ToStun = StaticCast<StunStatus*>(value.Get())) {
					if (ToStun->GetActivateStatus()) return;
					ToStun->BuildingUp(inBuildup);
					return;
				}
			}
		}
		TSharedPtr<BaseStatusEffect> newStatus = MakeShared<StunStatus>();
		CurEffectList->Add(newStatus);
		newStatus->SetOwningCharacter(OwningCharacter);
		newStatus->SetAffectedCharacter(AffectedCharacter);
		if (StunStatus* ToStun = StaticCast<StunStatus*>(newStatus.Get()))
			ToStun->BuildingUp(inBuildup);
	}
}


Metal::Metal()
{
	ElementalName = "Metal";
}

void Metal::ApplyStatusEffect(ABaseCharacter* AffectedCharacter)
{
	if (AffectedCharacter) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			TSharedPtr<BaseStatusEffect> value = (*CurEffectList)[i];
			if (value.IsValid() && value->GetStatusName().IsEqual("Bleed")) return;
		}
		TSharedPtr<BaseStatusEffect> newStatus = MakeShared<BleedStatus>();
		CurEffectList->Add(newStatus);
		newStatus->SetOwningCharacter(OwningCharacter);
		newStatus->SetAffectedCharacter(AffectedCharacter);
		newStatus->ExecuteStatus();
	}
}

Plant::Plant()
{
	ElementalName = "Plant";
}

void Plant::ApplyDrowsyEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter) {
		auto CurEffectList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurEffectList->Num(); ++i) {
			TSharedPtr<BaseStatusEffect> value = (*CurEffectList)[i];
			if (value.IsValid() && value->GetStatusName().IsEqual("Drowsy")) {
				if (DrowsyStatus* ToDrowsy = StaticCast<DrowsyStatus*>(value.Get())) {
					if (ToDrowsy->GetActivateStatus()) return;
					ToDrowsy->BuildingUp(inBuildup);
					return;
				}
			}
		}
		TSharedPtr<BaseStatusEffect> newStatus = MakeShared<DrowsyStatus>();
		CurEffectList->Add(newStatus);
		newStatus->SetOwningCharacter(OwningCharacter);
		newStatus->SetAffectedCharacter(AffectedCharacter);
		if (DrowsyStatus* ToDrowsy = StaticCast<DrowsyStatus*>(newStatus.Get()))
			ToDrowsy->BuildingUp(inBuildup);
	}
}
