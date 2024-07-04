// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../ProjectIncludes.h"
#include "AttackImpact.generated.h"

UCLASS()
class ELEMENTALCROWN_API AAttackImpact : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackImpact();
	AAttackImpact(const TCHAR* Ref);
protected:
	UPaperFlipbookComponent* AttackImpact = nullptr;
	UPaperFlipbook* ImpactFB = nullptr;

	FTimerHandle ImpactHandle;
public:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
