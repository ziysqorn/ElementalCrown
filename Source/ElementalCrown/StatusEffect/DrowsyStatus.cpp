#include "DrowsyStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

DrowsyStatus::DrowsyStatus()
{
	StatusName = "Drowsy";
	AffectingTime = 3.0f;
}

DrowsyStatus::~DrowsyStatus()
{
	if(DrowsyEffect) DrowsyEffect->Destroy();
	if (AffectedCharacter) {
		AffectedCharacter->SetCharacterState(CharacterState::NONE);
		if(AffectedCharacter->GetWorldTimerManager().IsTimerActive(EffectHandle))
			AffectedCharacter->GetWorldTimerManager().ClearTimer(EffectHandle);
	}
}

void DrowsyStatus::BuildingUp(const float& inBuildup)
{
	CurrentProgress += inBuildup;
	if (CurrentProgress >= BuildupToFill) {
		isActivated = true;
		this->ExecuteStatus();
	}
}

void DrowsyStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		DrowsyEffect = AffectedCharacter->GetWorld()->SpawnActor<ADrowsy>(ADrowsy::StaticClass(), AffectedCharacter->GetActorLocation(), AffectedCharacter->GetActorRotation(), SpawnParams);
		if (DrowsyEffect) {
			DrowsyEffect->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			DrowsyEffect->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
			DrowsyEffect->SetActorRelativeScale3D(FVector(2.0f, 0.0f, 2.0f));
			DrowsyEffect->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			AffectedCharacter->SetCharacterState(CharacterState::DROWSY);
			AffectedCharacter->GetWorldTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
				auto CurStatusList = AffectedCharacter->GetStatusList();
				for (int i = 0; i < CurStatusList->Num(); ++i) {
					TSharedPtr<BaseStatusEffect> cur = (*CurStatusList)[i];
					if (cur->GetStatusName() == "Drowsy") CurStatusList->RemoveAt(i);
				}
				}), AffectingTime, false);
		}
	}
}
