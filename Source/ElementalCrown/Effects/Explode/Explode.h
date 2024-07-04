// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "Explode.generated.h"

UCLASS()
class ELEMENTALCROWN_API AExplode : public AActor
{
	GENERATED_BODY()
protected:
	UPaperFlipbookComponent* ExplodeFBComp = nullptr;
	UPaperFlipbook* ExplodeFB = nullptr;

	//********************* TIMER HANDLES **************************
	FTimerHandle DestroyHandle;
	
public:	
	// Sets default values for this actor's properties
	AExplode();
	AExplode(const TCHAR* Ref);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
