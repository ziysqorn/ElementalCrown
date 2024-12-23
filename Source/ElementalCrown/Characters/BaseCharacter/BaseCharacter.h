// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../GameplayElemental/Elemental.h"
#include "../../StatusEffect/StatusEffectComponent.h"
#include "../../Skill/SkillComponent.h"
#include "../../Effects/StatsPopout/StatsPopout.h"
#include "../../Interface/GameplayInterface.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */
using namespace Constants;

UCLASS()
class ELEMENTALCROWN_API ABaseCharacter : public APaperZDCharacter, public IGameplayInterface
{
	GENERATED_BODY()
protected:
	FName CharacterName;
	UPROPERTY(Transient)
	UElemental* CharacterElement = nullptr;
	//Character's base stats
	int MaxHealth{ Default_Character_MaxHealth };
	int MaxMana{ Default_Character_MaxMana };
	int ATK_Damage{ Default_Character_ATKDamage };
	//Character's gameplay temporary stats
	int CurrentHealth{ MaxHealth };
	int CurrentMana{ MaxMana };
	//Can character dodge ?
	bool canDodge = true;
	//Animation sequences
	//Attack sequence
	UPROPERTY(EditDefaultsOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* AttackSequence = nullptr;
	//Hurt sequence
	UPROPERTY(EditDefaultsOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* HurtSequence = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* DeathSequence = nullptr;
	//Character's Current State
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Current State")
	CharacterState CurrentState = CharacterState::NONE;

	//Flash when damaged curve float
	UPROPERTY(EditDefaultsOnly, Category = "Important | CurveFloats | FlashCurveFloat")
	UCurveFloat* FlashCurveFloat = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Stats pop out subclass")
	TSubclassOf<AStatsPopout> StatsPopoutSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Status effect manager component")
	UStatusEffectComponent* StatusEffectComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Skill manager component")
	USkillComponent* SkillComponent = nullptr;

	FTimerHandle HurtHandle;
	FTimerHandle DeathHandle;
	FTimerHandle AttackHandle;
	FTimerHandle StunHandle;
	FTimerHandle HitStopHandle;
	FTimerHandle DodgeHandle;
	FTimerHandle DodgeEnableHandle;

	//Flash when damaged timeline
	FTimeline FlashTimeline;

public:
	ABaseCharacter();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	//Event taking damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	//Event landed
	void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	virtual void Dead() {};


	int GetMaxHealth() {
		return MaxHealth;
	}
	int GetCurrentHealth() {
		return CurrentHealth;
	}
	int GetCurrentMana() {
		return CurrentMana;
	}
	int GetMaxMana() {
		return MaxMana;
	}
	UFUNCTION()
	float GetHealthPercentage() const {
		return (float)CurrentHealth / MaxHealth;
	}
	UFUNCTION()
	float GetManaPercentage() {
		return (float)CurrentMana / MaxMana;
	}

	UFUNCTION()
	FName& GetCharacterName() {
		return CharacterName;
	}

	UElemental* GetElemental() override { 
		return CharacterElement; 
	}
	CharacterState GetCharacterState() { 
		return CurrentState; 
	}
	FTimerHandle& GetHitStopHandle() { 
		return HitStopHandle; 
	}
	UStatusEffectComponent* GetStatusEffectComp() {
		return StatusEffectComponent;
	}
	USkillComponent* GetSkillComp() {
		return SkillComponent;
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
	void SetCurrentHealthByBuff(const int& Buff) {
		int finalHealth = CurrentHealth + Buff;
		if (finalHealth > MaxHealth) CurrentHealth = MaxHealth;
		else if (finalHealth < 0) CurrentHealth = 0;
		else CurrentHealth = finalHealth;
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
	
	//Return character damage amount after a buff (or debuff)
	virtual int CalculatedDamage(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < ATK_Damage) || Buff >= 0) {
			return ATK_Damage + Buff;
		}
		return 0;
	}

	void SetManaAfterConsume(const int& Amount) {
		CurrentMana -= Amount;
		CurrentMana < 0 ? this->CurrentMana = 0 : this->CurrentMana = this->CurrentMana;
	}

	void SetCurrentManaByBuff(const int& Buff) {
		int finalMana = CurrentMana + Buff;
		if (finalMana > MaxMana) CurrentMana = MaxMana;
		else if (finalMana < 0) CurrentMana = 0;
		else CurrentMana = finalMana;
	}
};
