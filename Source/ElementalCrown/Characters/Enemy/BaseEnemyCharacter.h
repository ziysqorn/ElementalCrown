// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "../../UI/EnemyHealthBar/EnemyHealthBar.h"
#include "BaseEnemyCharacter.generated.h"

/**
 *
 */
using namespace Constants;
UCLASS()
class ELEMENTALCROWN_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	float AttackSpeed{ Default_Character_AttackSpeed };
protected:
	//Timer Handles
	FTimerHandle TurnBackHandle;
	FTimerHandle AttackRecoverHandle;
	//Size of the box that detects player
	FVector PlayerDetectBox = FVector(150, 0, 40);
	//Size of the box that detects wall
	FVector WallDetectBox = FVector(20, 0, 40);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character current state")
	//Decide if character can attack
	bool AttackRecovered{ true };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Health Bar")
	UWidgetComponent* EnemyHealthBar = nullptr;
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
