// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackAnimNotify.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "SpawnableSkillAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API USpawnableSkillAnimNotify : public UAttackAnimNotify
{
	GENERATED_BODY()
protected:
	mutable FVector SpawnLocation = FVector(0, 0, 0);
    mutable FRotator SpawnRotation = FRotator(0, 0, 0);
	mutable float SpawnDistanceX = 0.0f;
	//Done using this skill
	mutable FTimerHandle FinishSkill;
public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	void SetSpawnProperty(UPaperZDAnimInstance* OwningInstance);

	template<typename ActorClass>
	void SpawnSkillActor(UPaperZDAnimInstance* OwningInstance) const {
		if (OwningInstance) {
			if (OwningInstance->GetOwningActor()) {
				if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = BaseCharacter;
					BaseCharacter->GetWorld()->SpawnActor<ActorClass>(ActorClass::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				}
			}
		}
	};
};
