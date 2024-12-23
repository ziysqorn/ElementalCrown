// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../ProjectIncludes.h"
#include "../../Explode/FireArrowExplode/FireArrowExplode.h"
#include "../../../Characters/BaseCharacter/BaseCharacter.h"
#include "MagicArrow.generated.h"

UCLASS()
class ELEMENTALCROWN_API AMagicArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicArrow();
	AMagicArrow(const TCHAR* Ref);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	//Attribute
	int Buff{0};
	UPaperFlipbookComponent* ArrowComponent = nullptr;
	UPaperFlipbook* ArrowFB = nullptr;
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	FTimerHandle DestroyHandle;
	FTimerHandle ExpiredHandle;
	FTimerHandle SparkHandle;
public:
	virtual void SetBuff();
	//Events
	//Event hit 
	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	UFUNCTION()
	//Event begin overlap other actor
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void SelfDestroy();
};
