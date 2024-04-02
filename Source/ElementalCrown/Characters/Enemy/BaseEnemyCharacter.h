// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "../../Effects/Explode/Explode.h"
#include "../../GameplayElemental/Elemental.h"
#include "../../Constants/Constants.h"
#include "../../Interface/BaseCharacterInterface.h"
#include "BaseEnemyCharacter.generated.h"

/**
 *
 */
using namespace Constants;
UCLASS()
class ELEMENTALCROWN_API ABaseEnemyCharacter : public ABaseCharacter, public IBaseCharacterInterface
{
	GENERATED_BODY()

protected:
	float AttackSpeed{ Default_Character_AttackSpeed };
	Elemental *ElementalType = nullptr;
protected:
	//Timer Handles
	FTimerHandle TurnBackHandle;
	FTimerHandle AttackRecoverHandle;
	//Animation sequences
	//Attack sequence
	UPROPERTY(EditDefaultsOnly, Category = "Animation Sequence")
	UPaperZDAnimSequence* AttackSequence = nullptr;
	//Hurt sequence
	UPROPERTY(EditDefaultsOnly, Category = "Animation Sequence")
	UPaperZDAnimSequence* HurtSequence = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Animation Sequence")
	UPaperZDAnimSequence* DeathSequence = nullptr;
	//Size of the box that detects player
	FVector PlayerDetectBox{ FVector(150, 0, 40) };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character current state")
	//Decide if character can attack
	bool AttackRecovered{ true };
public:
	//************************************* CONSTRUCTOR *****************************************
	ABaseEnemyCharacter();
	virtual ~ABaseEnemyCharacter();
	//************************************* EVENTS **********************************************************
	//Event Begin Play
	virtual void BeginPlay() override;
	//Event Tick
	virtual void Tick(float DeltaSeconds) override;
	//Event taking damage
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	//Event landed
	void Landed(const FHitResult& Hit) override;
	//************************************* ACTIONS *********************************************************
	//Moving
	virtual void Move();
	//Attack
	virtual void Attack();
	//Detecting player . Return true if detected player location away 50 units from this character
	virtual bool DetectingPlayer();
	//Detecting wall
	bool DetectingWall();
};
