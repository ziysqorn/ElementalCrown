// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "BaseSkill.generated.h"

class ABaseCharacter;

UCLASS()
class ELEMENTALCROWN_API UBaseSkill : public UObject
{
	GENERATED_BODY()

protected:
	//Skill name
	FName SKillName;
	//Skill cooldown time
	float CurrentCooldown = 0.0f;
	float CooldownTime;
	//Mana consumption
	int ManaConsumption = 5;
	//Skill price
	int SkillPrice;
	//Return true if this skill can be used
	bool isAvailable = true;

	//*********************TIMER HANDLE**************************
	FTimerHandle CountdownProgHandle;

	//*********************SKILL SPRITE**************************
	UPaperSprite* SkillSprite = nullptr;
	
public:	
	// Sets default values for this actor's properties
	UBaseSkill();
	UBaseSkill(const TCHAR* Ref);

	void SetPrice(int price) {
		SkillPrice = price;
	}
	//******************** GETTER *******************************
	//Get this skill's availability
	bool GetAvailability() {
		return this->isAvailable;
	}
	UPaperSprite* GetSkillSprite() {
		return SkillSprite;
	}
	FName& GetSkillName() {
		return SKillName;
	}
	int GetManaConsumption() {
		return ManaConsumption;
	}
	int GetPrice() {
		return SkillPrice;
	}
	//******************** ACTION *******************************
	//Perform this skill
	virtual void PerformSkill();

	void CooldownSkill();
};
