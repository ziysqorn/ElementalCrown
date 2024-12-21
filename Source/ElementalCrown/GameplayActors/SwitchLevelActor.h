// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../CustomSave/GameProgress.h"
#include "SwitchLevelActor.generated.h"

UCLASS()
class ELEMENTALCROWN_API ASwitchLevelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitchLevelActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Root Scene")
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Switch Level Box")
	UBoxComponent* SwitchLevelBox = nullptr;

	UPROPERTY(EditAnywhere, Category = "Next Level Name")
	FName NextLevelName;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
