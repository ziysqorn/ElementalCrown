// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "PaperZDAnimInstance.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"
#include "../GameplayElemental/Elemental.h"

class Elemental;
class ELEMENTALCROWN_API BaseSkill
{
protected:
	//Skill name
	FName SKillName;
	//Skill cooldown time
	float CooldownTime;
	//This skill's owner
	ABaseCharacter* OwningCharacter = nullptr;
	Elemental* SkillElement = nullptr;
	//Return true if this skill can be used
	bool isAvailable{ true };

	float StunTime{ 0.00f };

	//*********************TIMER HANDLE**************************
	FTimerHandle RefreshSkillHandle;

	//*********************SKILL SPRITE**************************
	UPaperSprite* SkillSprite = nullptr;
	
public:	
	// Sets default values for this actor's properties
	BaseSkill();
	BaseSkill(const TCHAR* Ref);
	virtual ~BaseSkill();
	//Set this skill's owner;
	void SetOwningCharacter(ABaseCharacter* Character) {
		OwningCharacter = Character;
	}
	//******************** GETTER *******************************
	//Get this skill's availability
	bool GetAvailability() {
		return this->isAvailable;
	}
	float GetStunTime() {
		return this->StunTime;
	}
	UPaperSprite* GetSkillSprite() {
		return SkillSprite;
	}
	FName GetName() {
		return SKillName;
	}
	//******************** ACTION *******************************
	//Perform this skill
	virtual void PerformSkill() {};
};
