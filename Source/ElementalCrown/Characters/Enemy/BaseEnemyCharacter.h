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
	UPROPERTY()
	float AttackSpeed = Default_Character_AttackSpeed;

	UPROPERTY()
	bool isMovingAllowed = true;

	UPROPERTY()
	int maxBountyPrice = 12;
protected:
	//Timer Handles
	UPROPERTY()
	FTimerHandle TurnBackHandle;
	UPROPERTY()
	FTimerHandle AttackRecoverHandle;
	//Distance X to trigger attack
	UPROPERTY(EditDefaultsOnly, Category = "Important | Attack Trigger DistanceX")
	float AttackTriggerDistanceX = 70.0f;
	//Size of the box that detects player
	UPROPERTY(EditDefaultsOnly, Category = "Important | Player Detect Box")
	FVector PlayerDetectBox = FVector(250.0f, 0.0f, 40.0f);
	UPROPERTY(EditDefaultsOnly, Category = "Important | Player Detect Box Position")
	FVector PlayerDetectBoxPos = FVector(0.0f, 0.0f, 0.0f);
	//Size of the box that detects wall
	UPROPERTY(EditDefaultsOnly, Category = "Important | Wall Detect Box")
	FVector WallDetectBox = FVector(20.0f, 0.0f, 30.0f);
	UPROPERTY(EditDefaultsOnly, Category = "Important | Edge Detect Start Point")
	FVector EdgeDetectStartPoint = FVector(50.0f, 0.0f, 0.0f);

	//Decide if character can attack
	UPROPERTY()
	bool AttackRecovered = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Important | Enemy Health Bar")
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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//************************************* ACTIONS *********************************************************
	//Moving
	virtual void Move();

	//Attack
	virtual void Attack();

	virtual void Dead() override;
	
	void TurnBackAfterTime();

	void TurnBackAfterTakingDamage(AController* EventInstigator);

	UFUNCTION()
	void TurnBackImmediate();

	//Detecting player . Return true if detected player location away 50 units from this character
	virtual bool DetectingPlayer();

	//Detecting wall
	bool DetectingPatrolLimit();

	bool DetectingEdge();

	void SetIsMovingAllowed(bool isAllowed) {
		isMovingAllowed = isAllowed;
	}

	void SetAttackRecovered(bool inBool) {
		AttackRecovered = inBool;
	}

	void DestroyAfterDead() {
		this->Destroy();
	}
};
