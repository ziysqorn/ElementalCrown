// Fill out your copyright notice in the Description page of Project Settings.


#include "EjectSkill.h"

EjectSkill::EjectSkill()
{
	this->CooldownTime = 4.00f;
}

EjectSkill::~EjectSkill()
{
}

void EjectSkill::PerformSkill()
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
