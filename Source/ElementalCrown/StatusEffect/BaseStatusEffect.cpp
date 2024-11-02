// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatusEffect.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"

UBaseStatusEffect::UBaseStatusEffect()
{

}

void UBaseStatusEffect::BeginDestroy()
{
	Super::BeginDestroy();

	if (StatusEffectActor) StatusEffectActor->Destroy();
	if (GetWorld()->GetTimerManager().IsTimerActive(EffectHandle)) GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
	if (GetWorld()->GetTimerManager().IsTimerActive(ResetHandle) || GetWorld()->GetTimerManager().IsTimerPending(ResetHandle))
		GetWorld()->GetTimerManager().ClearTimer(ResetHandle);
}

void UBaseStatusEffect::RemoveStatusFromList()
{
	auto CurStatusList = AffectedCharacter->GetStatusList();
	for (int i = 0; i < CurStatusList->Num(); ++i) {
		UBaseStatusEffect* cur = (*CurStatusList)[i];
		if (cur->GetStatusName().IsEqual(StatusName)) {
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
					if (MainHUD) MainHUD->RemoveStatsEffectFromVerBox(i);
				}
			}
			UBaseStatusEffect* value = (*CurStatusList)[i];
			(*CurStatusList)[i] = nullptr;
			CurStatusList->RemoveAt(i);
			value->ConditionalBeginDestroy();
			return;
		}
	}
}

void UBaseStatusEffect::RemoveStatusFromList(const int& idx)
{
	auto CurStatusList = AffectedCharacter->GetStatusList();
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
		if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
			UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
			if (MainHUD) MainHUD->RemoveStatsEffectFromVerBox(idx);
		}
	}
	UBaseStatusEffect* value = (*CurStatusList)[idx];
	(*CurStatusList)[idx] = nullptr;
	CurStatusList->RemoveAt(idx);
	value->ConditionalBeginDestroy();
}

void UBaseStatusEffect::BuildingUp(const float& inBuildup)
{
	CurrentProgress += inBuildup;
	if (GetWorld()->GetTimerManager().IsTimerActive(ResetHandle) || GetWorld()->GetTimerManager().IsTimerPending(ResetHandle)) {
		GetWorld()->GetTimerManager().ClearTimer(ResetHandle);
	}
	if (CurrentProgress >= BuildupToFill) {
		isActivated = true;
		auto CurStatusList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < CurStatusList->Num(); ++i) {
			UBaseStatusEffect* cur = (*CurStatusList)[i];
			if (cur == this) {
				if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedCharacter)) {
					if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
						UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
						if (MainHUD) {
							UStatusEffectProgressUI* ProgressUI = MainHUD->GetStatusProgressUI(i);
							if (ProgressUI)
								ProgressUI->GetProgressBar()->PercentDelegate.Clear();
								ProgressUI->GetProgressBar()->PercentDelegate.BindUFunction(this, FName("GetTimePercentage"));
						}
					}
				}
				break;
			}
		}
		this->ExecuteStatus();
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(ResetHandle, FTimerDelegate::CreateLambda([this]() {
		CurrentProgress -= 0.1f;
		if (CurrentProgress <= 0.0f) this->RemoveStatusFromList();
		}), TimeForAReset, true, 2.0f);
}
