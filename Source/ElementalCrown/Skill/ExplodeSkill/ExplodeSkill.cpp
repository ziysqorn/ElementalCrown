// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodeSkill.h"

ExplodeSkill::ExplodeSkill()
{
	CooldownTime = 7.00f;
	SpawnDistanceX = 50.00f;
	ManaConsumption = 5;
}

ExplodeSkill::ExplodeSkill(const TCHAR* Ref) : BaseSkill(Ref)
{
	CooldownTime = 7.00f;
	SpawnDistanceX = 50.00f;
}

ExplodeSkill::~ExplodeSkill()
{
}

void ExplodeSkill::PerformSkill()
{
	if (OwningCharacter) {
		OwningCharacter->SetCharacterState(CharacterState::USESKILL);
		this->isAvailable = false;
		OwningCharacter->GetWorldTimerManager().SetTimer(this->RefreshSkillHandle, FTimerDelegate::CreateLambda([this]() {
			this->isAvailable = true;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Refresh"));
		}), this->CooldownTime, false);
	}
}
