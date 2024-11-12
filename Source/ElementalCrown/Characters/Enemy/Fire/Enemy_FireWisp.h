// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Fire.h"
#include "Enemy_FireWisp.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AEnemy_FireWisp : public AEnemy_Fire
{
	GENERATED_BODY()
protected:
	int DeathCountdown = 3;
	bool isCountdowning = false;

public:
	AEnemy_FireWisp();

	//Event Tick
	void Tick(float DeltaSeconds) override;

	void Attack() override {};

	bool DetectingPlayer() override;

	void SelfDestroy();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
