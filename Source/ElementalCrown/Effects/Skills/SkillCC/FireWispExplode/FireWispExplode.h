// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillCCEffect.h"
#include "FireWispExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AFireWispExplode : public ASkillCC
{
	GENERATED_BODY()

public:
	AFireWispExplode();
	void BeginPlay() override;
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
