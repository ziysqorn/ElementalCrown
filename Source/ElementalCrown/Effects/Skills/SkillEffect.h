// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../GameplayElemental/Elemental.h"
#include "../../Interface/GameplayInterface.h"
#include "SkillEffect.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASkillEffect : public AActor, public IGameplayInterface
{
	GENERATED_BODY()
protected:
	float SkillDamage{ 2.00f };

	float BuildupAmount;

	UPROPERTY()
	UPaperFlipbookComponent* FlipbookComponent = nullptr;
	UPROPERTY()
	UPaperFlipbook* Flipbook = nullptr;
	UPROPERTY()
	UElemental* EffectElement = nullptr;

	//********************* TIMER HANDLES **************************
	FTimerHandle DestroyHandle;
public:	
	// Sets default values for this actor's properties
	ASkillEffect();
	ASkillEffect(const TCHAR* Ref);
	~ASkillEffect();
	UElemental* GetElemental() override { return EffectElement; }
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Event On actor begin overlap
	UFUNCTION()
	virtual void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {};
};
