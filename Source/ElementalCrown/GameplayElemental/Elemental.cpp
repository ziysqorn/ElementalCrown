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
			if (UBaseStatusEffect* value = EffectComponent->FindStatusEffect("Burn")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			UBaseStatusEffect* newStatus = NewObject<UBurnStatus>(EffectComponent);
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
			if (UBaseStatusEffect* value = EffectComponent->FindStatusEffect("Vulnerable")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			UBaseStatusEffect* newStatus = NewObject<UVulnerableStatus>(EffectComponent);
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
			if (UBaseStatusEffect* value = EffectComponent->FindStatusEffect("Stun")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			UBaseStatusEffect* newStatus = NewObject<UStunStatus>(EffectComponent);
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
			if (UBaseStatusEffect* value = EffectComponent->FindStatusEffect("Bleed")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			UBaseStatusEffect* newStatus = NewObject<UBleedStatus>(EffectComponent);
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
			if (UBaseStatusEffect* value = EffectComponent->FindStatusEffect("Drowsy")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(OwningChar, inBuildup);
				return;
			}
			UBaseStatusEffect* newStatus = NewObject<UDrowsyStatus>(EffectComponent);
			EffectComponent->AddStatusEffect(newStatus);
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(OwningChar, inBuildup);
		}
	}
}
