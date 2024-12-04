// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableComponent.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"
#include "../CustomSave/GameplaySave.h"
#include "../CustomStructures/ConsumableData.h"

// Sets default values for this component's properties
UConsumableComponent::UConsumableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UConsumableComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UConsumableComponent::IsValidQuantityAfterAdding(UConsumable* Consumable, int Quantity)
{
	int idx = ConsumableList.Find(Consumable);
	if (idx != INDEX_NONE) {
		return (*Consumable->GetCurrentQuant()) + Quantity <= (*Consumable->GetMaxQuant());
	}
	return false;
}

bool UConsumableComponent::IsValidQuantityAfterAdding(FName inName, int Quantity)
{
	UConsumable** FoundConsumable = ConsumableList.FindByPredicate([inName](UConsumable* a) {
		return a->GetConsumableName().IsEqual(inName);
	});
	if (FoundConsumable) {
		UConsumable* Consumable = (*FoundConsumable);
		return (*Consumable->GetCurrentQuant()) + Quantity <= (*Consumable->GetMaxQuant());
	}
	return false;
}

void UConsumableComponent::UsePotion(UConsumable* DesiredConsumable)
{
	if (canConsume) {
		int idx = ConsumableList.Find(DesiredConsumable);
		if (idx == INDEX_NONE) return;
		if (ConsumableList[idx]->Consume()) {
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
						UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(idx);
						if (ConsumableSlot) {
							ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(ConsumableList[idx]->GetCurrentQuant()))));
							GetWorld()->GetTimerManager().SetTimer(ConsumeCooldownHandle, FTimerDelegate::CreateLambda([this]() {
								canConsume = true;
								}), 1.0f, false);
						}
					}
				}
			}
		}
	}
}

void UConsumableComponent::UsePotion(const FInputActionValue& inputValue, int idx)
{
	if (canConsume) {
		if (ConsumableList.IsValidIndex(idx)) {
			if (ConsumableList[idx]->Consume()) {
				if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
					if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
						if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
							UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(idx);
							if (ConsumableSlot) {
								ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(ConsumableList[idx]->GetCurrentQuant()))));
								GetWorld()->GetTimerManager().SetTimer(ConsumeCooldownHandle, FTimerDelegate::CreateLambda([this]() {
									canConsume = true;
									}), 1.0f, false);
							}
						}
					}
				}
			}
		}
	}
}

bool UConsumableComponent::AddPotionQuantity(UConsumable* DesiredConsumable, int Quantity)
{
	int idx = ConsumableList.Find(DesiredConsumable);
	if (idx == INDEX_NONE) return false;
	int* curQuant = ConsumableList[idx]->GetCurrentQuant();
	if (*curQuant + Quantity <= *(ConsumableList[idx]->GetMaxQuant())) {
		*curQuant += Quantity;
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(idx);
					if (ConsumableSlot) {
						ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(ConsumableList[idx]->GetCurrentQuant()))));
					}
				}
			}
		}
		return true;
	}
	return false;
}

int UConsumableComponent::AddPotionQuantity(FName ConsumableName, int Quantity)
{
	UConsumable** FoundConsumablePtr = ConsumableList.FindByPredicate([ConsumableName](UConsumable* a) {
		return a->GetConsumableName().IsEqual(ConsumableName);
	});
	int curQuant = 0;
	if (FoundConsumablePtr) {
		UConsumable* FoundCosumable = (*FoundConsumablePtr);
		int& curQuantRef = *(FoundCosumable->GetCurrentQuant());
		if (curQuantRef + Quantity <= *(FoundCosumable->GetMaxQuant())) {
			curQuantRef += Quantity;
			curQuant = curQuantRef;
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
						UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(ConsumableList.Find(FoundCosumable));
						if (ConsumableSlot) {
							ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(FoundCosumable->GetCurrentQuant()))));
						}
					}
				}
			}
		}
	}
	return curQuant;
}

void UConsumableComponent::AddPotion(UConsumable* Consumable)
{
	int idx = ConsumableList.Find(Consumable);
	if (idx != INDEX_NONE) return;
	ConsumableList.Add(Consumable);
}

bool UConsumableComponent::ReducePotion(UConsumable* DesiredConsumable, int Quantity)
{
	int idx = ConsumableList.Find(DesiredConsumable);
	if (idx == INDEX_NONE) return false;
	int* curQuant = ConsumableList[idx]->GetCurrentQuant();
	if (*curQuant - Quantity >= 0) {
		*curQuant -= Quantity;
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
					UConsumableSlot* ConsumableSlot = MainHUD->GetConsumableSlot(idx);
					if (ConsumableSlot) {
						ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(ConsumableList[idx]->GetCurrentQuant()))));
					}
				}
			}
		}
		return true;
	}
	return false;
}

void UConsumableComponent::LoadConsumable()
{
	ConsumableList.Empty();
	if (UGameplayStatics::DoesSaveGameExist("GameplaySave", 0)) {
		if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0))) {
			if (DT_Consumable) {
				const TArray<FName>& SavedConsumableList = GameplaySave->GetConsumableList();
				const TArray<int>& QuantList = GameplaySave->GetConsumableQuantList();
				for (int i = 0; i < SavedConsumableList.Num(); ++i) {
					if (FConsumableData* ConsumableData = DT_Consumable->FindRow<FConsumableData>(SavedConsumableList[i], "Lookup")) {
						UConsumable* NewConsumable = NewObject<UConsumable>(this, ConsumableData->DataClass);
						if (NewConsumable) {
							this->AddPotion(NewConsumable);
							NewConsumable->SetQuantity(QuantList[i]);
						}
					}
				}
			}
		}
	}
	else if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::CreateSaveGameObject(UGameplaySave::StaticClass()))) {
		if (DT_Consumable) {
			const TArray<FName>& RowNames = DT_Consumable->GetRowNames();
			for (int i = 0; i < RowNames.Num(); ++i) {
				TArray<FName>& SavedConsumableList = GameplaySave->GetConsumableList();
				SavedConsumableList.Add(RowNames[i]);
				if (FConsumableData* ConsumableData = DT_Consumable->FindRow<FConsumableData>(RowNames[i], "Lookup")) {
					if (UConsumable* NewConsumable = NewObject<UConsumable>(this, ConsumableData->DataClass)) {
						this->AddPotion(NewConsumable);
						GameplaySave->GetConsumableQuantList().Add(*(NewConsumable->GetCurrentQuant()));
					}
				}
			}
			UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
		}
	}
}
