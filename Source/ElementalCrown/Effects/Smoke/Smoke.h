// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "Smoke.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASmoke : public AActor
{
	GENERATED_BODY()
protected:
	//Destroy timer handle
	FTimerHandle DestroyHandle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DefaultRootComponent")
	USceneComponent* DefaultRootComponent = nullptr;
	// Flipbook component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FlipbookComponent")
	UPaperFlipbookComponent* FlipbookComponent = nullptr;
public:	
	// Sets default values for this actor's properties
	ASmoke();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SelfDestroy();
};
