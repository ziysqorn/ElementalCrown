// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoldComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTALCROWN_API UGoldComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	int CurrentGold = 100;


public:	
	// Sets default values for this component's properties
	UGoldComponent();

	int GetCurrentGold() {
		return CurrentGold;
	}

	void SetCurrentGold(int inGold) {
		if(inGold > 0) CurrentGold = inGold;
	}

	bool HaveEnoughGoldToBuy(int gold);

	void AddGold(int amount);

	bool ReduceGold(int amount);

	// Called when the game starts
	virtual void BeginPlay() override;
};
