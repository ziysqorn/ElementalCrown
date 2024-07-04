// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../GameplayElemental/Elemental.h"
#include "SkillEffect.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASkillEffect : public AActor
{
	GENERATED_BODY()
protected:
	float SkillDamage{ 2.00f };

	UPaperFlipbookComponent* FlipbookComponent = nullptr;
	UPaperFlipbook* Flipbook = nullptr;

	Elemental* EffectElement = nullptr;

	//********************* TIMER HANDLES **************************
	FTimerHandle DestroyHandle;
public:	
	// Sets default values for this actor's properties
	ASkillEffect();
	ASkillEffect(const TCHAR* Ref);
	~ASkillEffect();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Event On actor begin overlap
	UFUNCTION()
	virtual void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {};
};
