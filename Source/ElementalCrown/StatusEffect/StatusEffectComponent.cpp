// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"


UStatusEffectComponent::UStatusEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatusEffectComponent::AddStatusEffect(UBaseStatusEffect* Effect)
{
	if (Effect) {
		int findIdx = StatusList.Find(Effect);
		if (findIdx != INDEX_NONE) return;
		StatusList.Add(Effect);
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
				if (MainHUD) {
					TSubclassOf<UStatusEffectProgressUI>* ChosenSubclass = nullptr;
					if (Effect->GetStatusName().IsEqual("Burn")) ChosenSubclass = &BurnProgressSubClass;
					else if (Effect->GetStatusName().IsEqual("Vulnerable")) ChosenSubclass = &VulnerableProgSubClass;
					else if (Effect->GetStatusName().IsEqual("Stun")) ChosenSubclass = &StunProgressSubClass;
					else if (Effect->GetStatusName().IsEqual("Drowsy")) ChosenSubclass = &DrowsyProgressSubClass;
					else if (Effect->GetStatusName().IsEqual("Bleed")) ChosenSubclass = &BleedProgressSubClass;
					if (ChosenSubclass) {
						if (UStatusEffectProgressUI* ProgressUI = CreateWidget<UStatusEffectProgressUI>(MainHUD, *ChosenSubclass))
							MainHUD->AddStatsEffectToVerBox(ProgressUI);
					}
				}
			}
		}
	}
}

void UStatusEffectComponent::RemoveStatusEffect(UBaseStatusEffect* Effect)
{
	int removedIdx = StatusList.Find(Effect);
	if (removedIdx == INDEX_NONE) return;
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
		if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
			UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
			if (MainHUD) MainHUD->RemoveStatsEffectFromVerBox(removedIdx);
		}
	}
	StatusList.RemoveAt(removedIdx);
	Effect->ConditionalBeginDestroy();
}

void UStatusEffectComponent::ClearAllStatusEffect()
{
	for (int i = 0; i < StatusList.Num(); ++i) {
		UBaseStatusEffect* Effect = StatusList[i];
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
			if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
				UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
				if (MainHUD) MainHUD->RemoveStatsEffectFromVerBox(i);
			}
		}
		StatusList.RemoveAt(i);
		Effect->ConditionalBeginDestroy();
	}
}


UStatusEffectProgressUI* UStatusEffectComponent::GetProgressUI(UBaseStatusEffect* Effect)
{
	int findIdx = StatusList.Find(Effect);
	if (findIdx == INDEX_NONE) return nullptr;
	UStatusEffectProgressUI* ProgressUI = nullptr;
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
		if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
			UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
			if (MainHUD) ProgressUI = MainHUD->GetStatusProgressUI(findIdx);
		}
	}
	return ProgressUI;
}

void UStatusEffectComponent::BeginPlay()
{
	Super::BeginPlay();
}

