// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffect.h"
#include "../../../Characters/BaseCharacter/BaseCharacter.h"
#include "SkillProjectile.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASkillProjectile : public ASkillEffect
{
	GENERATED_BODY()

protected:
	//Projectile movement component
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	//Delay time to destroy this actor
	float DestroyDelay{ 4.00f };
public:	
	// Sets default values for this actor's properties
	ASkillProjectile();
	ASkillProjectile(const TCHAR* Ref);
	// Spawn explosion when this projectile hit an object
	virtual void SpawnExplosion() {};
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};

