// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillExplode.h"
#include "VolcanicFireExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AVolcanicFireExplode : public ASkillExplode
{
	GENERATED_BODY()
		friend class UVolcanicFireSlashAnimNotify;
protected:
	FTimerHandle DestroyHandle;
public:
	AVolcanicFireExplode();
	void BeginPlay() override;
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
