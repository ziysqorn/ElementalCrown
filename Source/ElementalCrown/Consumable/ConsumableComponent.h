// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "HPPotion/HPPotion.h"
#include "ManaPotion/ManaPotion.h"
#include "BurnCurePotion/BurnCurePotion.h"
#include "BleedCurePotion/BleedCurePotion.h"
#include "StunCurePotion/StunCurePotion.h"
#include "DrowsyCurePotion/DrowsyCurePotion.h"
#include "VulnerableCurePotion/VulnerableCurePotion.h"
#include "ConsumableComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTALCROWN_API UConsumableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<UConsumable*> ConsumableList;

	bool canConsume = true;

	FTimerHandle ConsumeCooldownHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Important")
	UDataTable* DT_Consumable = nullptr;

public:	
	// Sets default values for this component's properties
	UConsumableComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<UConsumable*>& GetConsumableList(){
		return ConsumableList;
	}

	UConsumable* FindConsumable(FName inName) {
		UConsumable** FoundConsumable = ConsumableList.FindByPredicate([inName](UConsumable* a) {
			return a->GetConsumableName().IsEqual(inName);
		});
		if (FoundConsumable) return *FoundConsumable;
		return nullptr;
	}

	bool IsValidQuantityAfterAdding(UConsumable* Consumable, int Quantity);

	bool IsValidQuantityAfterAdding(FName inName, int Quantity);

	void UsePotion(UConsumable* DesiredConsumable);

	void UsePotion(const FInputActionValue& inputValue, int idx);

	bool AddPotionQuantity(UConsumable* DesiredConsumable, int Quantity);

	int AddPotionQuantity(FName ConsumableName, int Quantity);

	void AddPotion(UConsumable* Consumable);

	bool ReducePotion(UConsumable* DesiredConsumable, int Quantity);

	void LoadConsumable();
};
