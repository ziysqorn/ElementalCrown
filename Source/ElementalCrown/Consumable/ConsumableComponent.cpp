// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableComponent.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"

// Sets default values for this component's properties
UConsumableComponent::UConsumableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	HealPotion = new HPPotion();

	MPPotion = new ManaPotion();
}


// Called when the game starts
void UConsumableComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (HealPotion && MPPotion) {
		HealPotion->SetOwningChar(Cast<ABaseCharacter>(this->GetOwner()));
		MPPotion->SetOwningChar(Cast<ABaseCharacter>(this->GetOwner()));
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UConsumableSlot* HealPotSlot = MainHUD->GetConsumableSlot(1);
					UConsumableSlot* ManaPotSlot = MainHUD->GetConsumableSlot(2);
					if (HealPotSlot && HealPotSlot) {
						HealPotSlot->SetQuantityText(FText::FromString(FString::FromInt(*(HealPotion->GetCurrentQuant()))));
						ManaPotSlot->SetQuantityText(FText::FromString(FString::FromInt(*(MPPotion->GetCurrentQuant()))));
					}
				}
			}
		}
	}
}

void UConsumableComponent::UseHealPot()
{
	if (HealPotion) {
		HealPotion->Consume();
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(1);
					if (ConsumableSlot) {
						ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(HealPotion->GetCurrentQuant()))));
					}
				}
			}
		}
	}
}

void UConsumableComponent::AddHealPotQuant(const int& Quantity)
{
	if (HealPotion) {
		int* curQuant = HealPotion->GetCurrentQuant();
		if (*curQuant + Quantity <= *(HealPotion->GetMaxQuant())) {
			*curQuant += Quantity;
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
						UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(1);
						if (ConsumableSlot) {
							ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(HealPotion->GetCurrentQuant()))));
						}
					}
				}
			}
		}
	}
}

void UConsumableComponent::ReduceHealPotQuant(const int& Quantity)
{
	if (HealPotion) {
		int* curQuant = HealPotion->GetCurrentQuant();
		if (*curQuant - Quantity >= 0) {
			*curQuant -= Quantity;
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
						UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(1);
						if (ConsumableSlot) {
							ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(HealPotion->GetCurrentQuant()))));
						}
					}
				}
			}
		}
	}
}

void UConsumableComponent::UseManaPot()
{
	if (MPPotion) {
		MPPotion->Consume();
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(2);
					if (ConsumableSlot) {
						ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(MPPotion->GetCurrentQuant()))));
					}
				}
			}
		}
	}
}

void UConsumableComponent::AddManaPotQuant(const int& Quantity)
{
	if (MPPotion) {
		int* curQuant = MPPotion->GetCurrentQuant();
		if (*curQuant + Quantity <= *(MPPotion->GetMaxQuant())) {
			*curQuant += Quantity;
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
						UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(2);
						if (ConsumableSlot) {
							ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(MPPotion->GetCurrentQuant()))));
						}
					}
				}
			}
		}
	}
}

void UConsumableComponent::ReduceManaPotQuant(const int& Quantity)
{
	if (MPPotion) {
		int* curQuant = MPPotion->GetCurrentQuant();
		if (*curQuant - Quantity >= 0) {
			*curQuant -= Quantity;
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
						UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(2);
						if (ConsumableSlot) {
							ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(MPPotion->GetCurrentQuant()))));
						}
					}
				}
			}
		}
	}
}
