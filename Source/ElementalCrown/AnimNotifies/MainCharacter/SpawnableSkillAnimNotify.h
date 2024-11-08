// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackAnimNotify.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "../../Effects/Skills/SkillEffect.h"
#include "SpawnableSkillAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API USpawnableSkillAnimNotify : public UPaperZDAnimNotify
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "SkillActorSubclass")
	TSubclassOf<AActor>  SkillActorSubclass;
	UPROPERTY(EditDefaultsOnly, Category = "AdditionalSpawnLoc")
	FVector AdditionalSpawnLoc = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditDefaultsOnly, Category = "AdditionalSpawnLoc")
	FRotator AdditionalSpawnRot = FRotator(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditDefaultsOnly, Category = "IsThisNotifyCustomed?")
	bool isCustom = false;
	//Done using this skill
	mutable FTimerHandle FinishSkill;
public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;

	template<typename ActorClass>
	void SpawnSkillActor(ABaseCharacter* BaseCharacter) const;

	void SpawnSkillActor(ABaseCharacter* BaseCharacter) const;
};
