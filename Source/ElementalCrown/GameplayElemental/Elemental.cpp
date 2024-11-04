// Fill out your copyright notice in the Description page of Project Settings.


#include "Elemental.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"
#include "../Effects/Skills/SkillEffect.h"

UElemental::UElemental()
{
}

UFire::UFire()
{
	ElementalName = "Fire";
}

void UFire::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		if (UStatusEffectComponent* EffectComponent = AffectedCharacter->GetStatusEffectComp()) {
			ABaseCharacter* OwningChar = nullptr;
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				OwningChar = BaseCharacter;
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				OwningChar = Cast<ABaseCharacter>(SkillEffect->GetOwner());
			}
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Burn")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new BurnStatus();
			EffectComponent->AddStatusEffect(newStatus);
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(OwningChar, inBuildup);
		}
	}
}

UWater::UWater()
{
	ElementalName = "Water";
}

void UWater::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		if (UStatusEffectComponent* EffectComponent = AffectedCharacter->GetStatusEffectComp()) {
			ABaseCharacter* OwningChar = nullptr;
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				OwningChar = BaseCharacter;
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				OwningChar = Cast<ABaseCharacter>(SkillEffect->GetOwner());
			}
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Vulnerable")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new VulnerableStatus();
			EffectComponent->AddStatusEffect(newStatus);
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(OwningChar, inBuildup);
		}
	}
}

UEarth::UEarth()
{
	ElementalName = "Earth";
}

void UEarth::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		if (UStatusEffectComponent* EffectComponent = AffectedCharacter->GetStatusEffectComp()) {
			ABaseCharacter* OwningChar = nullptr;
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				OwningChar = BaseCharacter;
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				OwningChar = Cast<ABaseCharacter>(SkillEffect->GetOwner());
			}
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Stun")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new StunStatus();
			EffectComponent->AddStatusEffect(newStatus);
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(OwningChar, inBuildup);
		}
	}
}


UMetal::UMetal()
{
	ElementalName = "Metal";
}

void UMetal::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		if (UStatusEffectComponent* EffectComponent = AffectedCharacter->GetStatusEffectComp()) {
			ABaseCharacter* OwningChar = nullptr;
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				OwningChar = BaseCharacter;
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				OwningChar = Cast<ABaseCharacter>(SkillEffect->GetOwner());
			}
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Bleed")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new BleedStatus();
			EffectComponent->AddStatusEffect(newStatus);
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(OwningChar, inBuildup);
		}
	}
}

UPlant::UPlant()
{
	ElementalName = "Plant";
}

void UPlant::ApplyStatusEffect(ABaseCharacter* AffectedCharacter, const float& inBuildup)
{
	if (AffectedCharacter && AffectedCharacter->GetCharacterState() != CharacterState::DEATH) {
		if (UStatusEffectComponent* EffectComponent = AffectedCharacter->GetStatusEffectComp()) {
			ABaseCharacter* OwningChar = nullptr;
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				OwningChar = BaseCharacter;
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				OwningChar = Cast<ABaseCharacter>(SkillEffect->GetOwner());
			}
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Drowsy")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new DrowsyStatus();
			EffectComponent->AddStatusEffect(newStatus);
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(OwningChar, inBuildup);
		}
	}
}
