// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffect.h"
#include "../../../Characters/BaseCharacter/BaseCharacter.h"
#include "SkillCCEffect.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ASkillCC : public ASkillEffect
{
	GENERATED_BODY()
protected:
	FVector LaunchVector = FVector(0.0f, 0.0f, 0.0f);
public:
	// Sets default values for this actor's properties
	ASkillCC();
	ASkillCC(const TCHAR* Ref);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
