// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "TurnBackPoint.generated.h"

UCLASS()
class ELEMENTALCROWN_API ATurnBackPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnBackPoint();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "RootSceneComponent")
	USceneComponent* RootSceneComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionBoxComp")
	UBoxComponent* CollisionBox = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
