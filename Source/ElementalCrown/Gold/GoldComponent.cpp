// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldComponent.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"

// Sets default values for this component's properties
UGoldComponent::UGoldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


}

bool UGoldComponent::HaveEnoughGoldToBuy(int gold)
{
	return CurrentGold >= gold;
}

void UGoldComponent::AddGold(int amount)
{
	if (amount >= 0) {
		CurrentGold += amount;

		if (AMainCharacter* MainCharacter = this->GetOwner<AMainCharacter>()) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					MainHUD->SetGoldText(FText::FromString(FString::FromInt(CurrentGold)));
				}
			}
		}
	}
}

bool UGoldComponent::ReduceGold(int amount)
{
	if (amount >= 0) {
		if (CurrentGold - amount < 0) return false;

		CurrentGold -= amount;
		if (AMainCharacter* MainCharacter = this->GetOwner<AMainCharacter>()) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					MainHUD->SetGoldText(FText::FromString(FString::FromInt(CurrentGold)));
				}
				return true;
			}
		}
	}
	return false;
}


// Called when the game starts
void UGoldComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


