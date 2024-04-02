// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "TimerManager.h"
#include "Smoke.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASmoke : public AActor
{
	GENERATED_BODY()
protected:
	//Destroy timer handle
	FTimerHandle DestroyHandle;
	// Flipbook component
	UPaperFlipbookComponent* FlipbookComponent = nullptr;
	// Flipbook to set
	UPaperFlipbook* SmokeFB = nullptr;
public:	
	// Sets default values for this actor's properties
	ASmoke();
	ASmoke(const TCHAR* Ref);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
