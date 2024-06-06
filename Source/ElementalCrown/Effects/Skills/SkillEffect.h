// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Skill/BaseSkill.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "SkillEffect.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASkillEffect : public AActor
{
	GENERATED_BODY()
protected:
	UPaperFlipbookComponent* FlipbookComponent = nullptr;
	UPaperFlipbook* Flipbook = nullptr;

	//The skill this effect belongs to
	BaseSkill* OwningSkill = nullptr;

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
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override {};
};
