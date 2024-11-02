#include "DrowsyStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

UDrowsyStatus::UDrowsyStatus()
{
	StatusName = "Drowsy";
	AffectingTime = 3.0f;
	TimeForAReset = 0.2f;
}

void UDrowsyStatus::BeginDestroy()
{
	Super::BeginDestroy();

	if (AffectedCharacter) {
		auto StatusList = AffectedCharacter->GetStatusList();
		for (int i = 0; i < StatusList->Num(); ++i) {
			if ((*StatusList)[i]->GetStatusName().IsEqual("Stun")) return;
		}
		if (AffectedCharacter->GetCharacterState() != CharacterState::DEATH)
			AffectedCharacter->SetCharacterState(CharacterState::NONE);
	}
}

void UDrowsyStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		StatusEffectActor = AffectedCharacter->GetWorld()->SpawnActor<ADrowsy>(ADrowsy::StaticClass(), AffectedCharacter->GetActorLocation(), AffectedCharacter->GetActorRotation(), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			StatusEffectActor->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
			StatusEffectActor->SetActorRelativeScale3D(FVector(2.0f, 0.0f, 2.0f));
			StatusEffectActor->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			if(AffectedCharacter->GetCharacterState() != CharacterState::DEATH) AffectedCharacter->SetCharacterState(CharacterState::STUN);
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
				TimeElapsed += 0.1f;
				if (TimeElapsed >= AffectingTime) this->RemoveStatusFromList();
			}), 0.1f, true);
		}
	}
}
