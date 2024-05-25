// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "GameFramework/Controller.h"
#include "Components/TimelineComponent.h"
#include "PaperFlipbookComponent.h"
#include "../../Skill/BaseSkill.h"
#include "../../Constants/Constants.h"
#include "../../Enums/Enums.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */
using namespace Constants;
class BaseSkill;
UCLASS()
class ELEMENTALCROWN_API ABaseCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
protected:
	//Character's base stats
	int MaxHealth{ Default_Character_MaxHealth };
	int ATK_Damage{ Default_Character_ATKDamage };
	int Resist{ Default_Character_Resist };
	uint8 DeStun{ Default_Character_DeStun };
	//Character's gameplay temporary stats
	int CurrentHealth{ MaxHealth };
	//Character's Current State
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Current State")
	CharacterState CurrentState = CharacterState::NONE;

	//Character current skill
	BaseSkill* Skill = nullptr;

	//Flash when damaged curve float
	UPROPERTY(EditDefaultsOnly, Category = "DamagedFlash | FlashCurveFloat")
	UCurveFloat* FlashCurveFloat = nullptr;

	FTimerHandle HurtHandle;
	FTimerHandle DeathHandle;
	FTimerHandle AttackHandle;
	FTimerHandle StunHandle;

	//Flash when damaged timeline
	FTimeline FlashTimeline;
public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	//Get character's current skill
	BaseSkill* GetCurrentSkill() {
		return this->Skill;
	}
	//Set character's current state
	void SetCharacterState(const CharacterState&& State) {
		this->CurrentState = State;
	}
	//Set Damage (min = 1) by a buff (pass in negative value = debuff)
	void SetATKDamageByBuff(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < ATK_Damage) || Buff >= 0) {
			ATK_Damage += Buff;
		}
		else {
			ATK_Damage = 1;
		}
	}
	//Set Damage (min = 0) directly by a new value
	void SetATKDamageByNewValue(const int& NewDamage) {
		if (NewDamage >= 0) {
			ATK_Damage = NewDamage;
		}
		else {
			ATK_Damage = 0;
		}
	}
	//Set max health (min = 1) by a buff (pass in negative value = debuff)
	void SetMaxHealthByBuff(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < MaxHealth) || Buff >= 0) {
			MaxHealth += Buff;
		}
		else {
			MaxHealth = 1;
		}
	}
	//Set max health (min=0) directly by a new value
	void SetMaxHealthByNewValue(const int& NewMaxHealth) {
		if (NewMaxHealth >= 0) {
			MaxHealth = NewMaxHealth;
		}
		else {
			MaxHealth = 0;
		}
	}
	//Set resist(min=1) by a buff (pass in negative value = debuff)
	void SetResistByBuff(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < Resist) || Buff >= 0) {
			Resist += Buff;
		}
		else {
			Resist = 1;
		}
	}
	//Set resist(min=0) directly by a new value
	void SetResistByNewValue(const int& NewResist) {
		if (NewResist >= 0) {
			Resist = NewResist;
		}
		else {
			Resist = 0;
		}
	}
	//Return character damage amount after a buff (or debuff)
	virtual int CalculatedDamage(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < ATK_Damage) || Buff >= 0) {
			return ATK_Damage + Buff;
		}
		return 0;
	}
};
