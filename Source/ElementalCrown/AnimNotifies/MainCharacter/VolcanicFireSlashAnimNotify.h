// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MainCharacter/SpawnableSkillAnimNotify.h"
#include "../../Effects/Skills/SkillExplode/VolcanicFireExplode/VolcanicFireExplode.h"
#include "VolcanicFireSlashAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UVolcanicFireSlashAnimNotify : public USpawnableSkillAnimNotify
{
	GENERATED_BODY()
protected:
	uint8 CurrentSpawnTime{ 1 };
	const uint8 MaxSpawnTimes{ 6 };
	//Spawn explosion timer handle
	FTimerHandle SpawnHandle;
public:
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) override;
	void SpawnContinuously(ABaseCharacter* OwningCharacter);
	
};
