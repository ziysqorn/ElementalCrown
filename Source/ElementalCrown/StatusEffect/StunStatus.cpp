#include "StunStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

StunStatus::StunStatus()
{
	StatusName = "Stun";
	AffectingTime = 2.5f;
}

StunStatus::~StunStatus()
{
	if (StunEffect) StunEffect->Destroy();
	if (AffectedCharacter) AffectedCharacter->SetCharacterState(CharacterState::NONE);
}

void StunStatus::BuildingUp(const float& inBuildup)
{
	CurrentProgress += inBuildup;
	if (CurrentProgress >= BuildupToFill) {
		isActivated = true;
		this->ExecuteStatus();
	}
}

void StunStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		StunEffect = AffectedCharacter->GetWorld()->SpawnActor<AStun>(AStun::StaticClass(), AffectedCharacter->GetActorLocation(), AffectedCharacter->GetActorRotation(), SpawnParams);
		if (StunEffect) {
			StunEffect->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			StunEffect->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
			StunEffect->SetActorRelativeScale3D(FVector(2.0f, 0.0f, 2.0f));
			StunEffect->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			AffectedCharacter->SetCharacterState(CharacterState::STUN);
			AffectedCharacter->GetWorldTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
				auto CurStatusList = AffectedCharacter->GetStatusList();
				for (int i = 0; i < CurStatusList->Num(); ++i) {
					TSharedPtr<BaseStatusEffect> cur = (*CurStatusList)[i];
					if (cur->GetStatusName() == "Stun") CurStatusList->RemoveAt(i);
				}
				}), AffectingTime, false);
		}
	}
}
