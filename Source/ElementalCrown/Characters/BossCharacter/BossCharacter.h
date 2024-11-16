// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Main Character/MainCharacter.h"
#include "../../UI/BossHealthBar/BossHealthBar.h"
#include "BossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ABossCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Important | Time amount for new decision")
	float NewDecisionTimeAmount = 1.5f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	int attackDecisionMode = 1;

	bool hasDealtDmgToPlayer = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* Attack2Sequence = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* SpecialAtkSequence = nullptr;

	FTimerHandle NewDecisionTimer;
public:
	ABossCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void Attack();

	virtual void ChangePos();

	virtual void MakeDecision();

	virtual void SetupHealthbar();



	/*void SetTargetMainChar(AMainCharacter* MainCharacter) {
		if (MainCharacter) TargetMainChar = MainCharacter;
	}*/
};
