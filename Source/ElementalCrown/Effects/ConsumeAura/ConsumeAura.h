// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../ProjectIncludes.h"
#include "ConsumeAura.generated.h"

UCLASS()
class ELEMENTALCROWN_API AConsumeAura : public AActor
{
	GENERATED_BODY()

protected:
	UPaperFlipbookComponent* StatusFlipbookComp = nullptr;
	UPaperFlipbookComponent* MirroredFlipbookComp = nullptr;

	FTimerHandle DestroyHandle;
public:	
	// Sets default values for this actor's properties
	AConsumeAura();
	AConsumeAura(const TCHAR* FlipbookRef);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SelfDestroy();
};
