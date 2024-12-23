// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatusEffect.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"

BaseStatusEffect::BaseStatusEffect()
{

}

BaseStatusEffect::~BaseStatusEffect()
{
	if (StatusEffectActor) StatusEffectActor->Destroy();

	UStatusEffectComponent* EffectComp = nullptr;
	if(AffectedChar) EffectComp = AffectedChar->GetStatusEffectComp();

	if (EffectComp) {
		if (EffectComp->GetWorld()->GetTimerManager().IsTimerActive(EffectHandle)) EffectComp->GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
		if (EffectComp->GetWorld()->GetTimerManager().IsTimerActive(ResetHandle) || EffectComp->GetWorld()->GetTimerManager().IsTimerPending(ResetHandle))
			EffectComp->GetWorld()->GetTimerManager().ClearTimer(ResetHandle);
	}
}

void BaseStatusEffect::BuildingUp(ABaseCharacter* OwningCharacter, const float& inBuildup)
{
	UStatusEffectComponent* EffectComp = nullptr;
	if (AffectedChar) EffectComp = AffectedChar->GetStatusEffectComp();

	if (EffectComp) {
		CurrentProgress += inBuildup;
		if (EffectComp->GetWorld()->GetTimerManager().IsTimerActive(ResetHandle) || EffectComp->GetWorld()->GetTimerManager().IsTimerPending(ResetHandle)) {
			EffectComp->GetWorld()->GetTimerManager().ClearTimer(ResetHandle);
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


		EffectComp->GetWorld()->GetTimerManager().SetTimer(ResetHandle, FTimerDelegate::CreateUObject(EffectComp, &UStatusEffectComponent::ReduceStatusBuildup, this), TimeForAReset, true, 2.0f);
	}
}
