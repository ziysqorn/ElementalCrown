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
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Burn")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new BurnStatus();
			EffectComponent->AddStatusEffect(newStatus);
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				newStatus->SetOwningCharacter(BaseCharacter);
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
			}
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(inBuildup);
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
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Vulnerable")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new VulnerableStatus();
			EffectComponent->AddStatusEffect(newStatus);
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				newStatus->SetOwningCharacter(BaseCharacter);
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
			}
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(inBuildup);
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
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Stun")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new StunStatus();
			EffectComponent->AddStatusEffect(newStatus);
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				newStatus->SetOwningCharacter(BaseCharacter);
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
			}
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(inBuildup);
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
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Bleed")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new BleedStatus();
			EffectComponent->AddStatusEffect(newStatus);
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				newStatus->SetOwningCharacter(BaseCharacter);
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
			}
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(inBuildup);
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
			if (BaseStatusEffect* value = EffectComponent->FindStatusEffect("Drowsy")) {
				if (value->GetActivateStatus()) return;
				value->BuildingUp(inBuildup);
				return;
			}
			BaseStatusEffect* newStatus = new DrowsyStatus();
			EffectComponent->AddStatusEffect(newStatus);
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(this->GetOuter())) {
				newStatus->SetOwningCharacter(BaseCharacter);
			}
			else if (ASkillEffect* SkillEffect = Cast<ASkillEffect>(this->GetOuter())) {
				newStatus->SetOwningCharacter(Cast<ABaseCharacter>(SkillEffect->GetOwner()));
			}
			newStatus->SetAffectedCharacter(AffectedCharacter);
			newStatus->BuildingUp(inBuildup);
		}
	}
}
