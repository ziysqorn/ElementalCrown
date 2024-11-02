#include "StunStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

UStunStatus::UStunStatus()
{
	StatusName = "Stun";
	AffectingTime = 2.5f;
	TimeForAReset = 0.3f;
}

void UStunStatus::BeginDestroy()
{
	Super::BeginDestroy();

	auto StatusList = AffectedCharacter->GetStatusList();
	for (int i = 0; i < StatusList->Num(); ++i) {
		if ((*StatusList)[i]->GetStatusName().IsEqual("Drowsy")) return;
	}
	if (AffectedCharacter->GetCharacterState() != CharacterState::DEATH)
		AffectedCharacter->SetCharacterState(CharacterState::NONE);

}

void UStunStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		StatusEffectActor = AffectedCharacter->GetWorld()->SpawnActor<AStun>(AStun::StaticClass(), AffectedCharacter->GetActorLocation(), AffectedCharacter->GetActorRotation(), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			StatusEffectActor->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
			StatusEffectActor->SetActorRelativeScale3D(FVector(2.0f, 0.0f, 2.0f));
			//StunEffect->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			if (AffectedCharacter->GetCharacterState() != CharacterState::DEATH) AffectedCharacter->SetCharacterState(CharacterState::STUN);
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
				TimeElapsed += 0.1f;
				if (TimeElapsed >= AffectingTime) this->RemoveStatusFromList();
			}), 0.1f, true);
		}
	}
}
