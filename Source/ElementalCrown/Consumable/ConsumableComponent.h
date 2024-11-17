// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HPPotion/HPPotion.h"
#include "ManaPotion/ManaPotion.h"
#include "ConsumableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTALCROWN_API UConsumableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	HPPotion* HealPotion = nullptr;

	ManaPotion* MPPotion = nullptr;


public:	
	// Sets default values for this component's properties
	UConsumableComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	void UseHealPot();

	void AddHealPotQuant(const int& Quantity);

	void ReduceHealPotQuant(const int& Quantity);

	void UseManaPot();

	void AddManaPotQuant(const int& Quantity);

	void ReduceManaPotQuant(const int& Quantity);
};
