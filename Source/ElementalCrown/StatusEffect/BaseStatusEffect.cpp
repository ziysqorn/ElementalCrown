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

	if (GetWorld()) {
		GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
		GetWorld()->GetTimerManager().ClearTimer(ResetHandle);
	}
}


void UBaseStatusEffect::ReduceStatusBuildup()
{
	if (IsValid(AffectedChar)) {
		if (UStatusEffectComponent* EffectComp = AffectedChar->GetStatusEffectComp()) {
			CurrentProgress -= 0.1f;
			if (CurrentProgress <= 0.0f) EffectComp->RemoveStatusEffect(this);
			else {
				if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedChar)) {
					if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
						UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
						if (MainHUD) {
							if (UStatusEffectProgressUI* ProgressUI = MainHUD->GetStatusProgressUI(EffectComp->FindStatusEffect(this))) {
								ProgressUI->GetProgressBar()->SetPercent(this->GetBuildupPercentage());
							}
						}
					}
				}
			}
		}
	}
}

void UBaseStatusEffect::AffectingCountdown()
{
	if (IsValid(AffectedChar)) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			TimeElapsed += 0.1f;
			if (TimeElapsed >= AffectingTime) {
				EffectComponent->RemoveStatusEffect(this);
				return;
			}
			if (UStatusEffectProgressUI* ProgressUI = EffectComponent->GetProgressUI(this)) {
				ProgressUI->GetProgressBar()->SetPercent(GetTimePercentage());
			} 
		}
	}
}

void UBaseStatusEffect::BuildingUp(ABaseCharacter* OwningCharacter, const float& inBuildup)
{
	if (IsValid(OwningCharacter) && IsValid(AffectedChar)) {
		if (UStatusEffectComponent* EffectComp = AffectedChar->GetStatusEffectComp()) {
			CurrentProgress += inBuildup;
			if (GetWorld()->GetTimerManager().IsTimerActive(ResetHandle) || GetWorld()->GetTimerManager().IsTimerPending(ResetHandle)) {
				GetWorld()->GetTimerManager().ClearTimer(ResetHandle);
			}

			UStatusEffectProgressUI* ProgressUI = nullptr;
			if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(AffectedChar)) {
				if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
					UMainCharacterHUD* MainHUD = MainController->GetMainHUD();
					if (MainHUD) {
						ProgressUI = MainHUD->GetStatusProgressUI(EffectComp->FindStatusEffect(this));
					}
				}
			}

			if (CurrentProgress >= BuildupToFill) {
				CurrentProgress = BuildupToFill;
				if (ProgressUI) ProgressUI->GetProgressBar()->SetPercent(this->GetBuildupPercentage());
				isActivated = true;
				OwningChar = OwningCharacter;
				this->ExecuteStatus();
				return;
			}

			if (ProgressUI) ProgressUI->GetProgressBar()->SetPercent(this->GetBuildupPercentage());


			GetWorld()->GetTimerManager().SetTimer(ResetHandle, FTimerDelegate::CreateUObject(this, &UBaseStatusEffect::ReduceStatusBuildup), TimeForAReset, true, 2.0f);
		}
	}
}
