// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffect.h"
#include "../../../Characters/BaseCharacter/BaseCharacter.h"
#include "SkillExplode.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASkillExplode : public ASkillEffect
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillExplode();
	ASkillExplode(const TCHAR* Ref);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
