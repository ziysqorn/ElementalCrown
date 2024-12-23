#include "StunStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

StunStatus::StunStatus()
{
	StatusName = "Stun";
	AffectingTime = 2.5f;
	TimeForAReset = 0.3f;
}

StunStatus::~StunStatus()
{
	if (AffectedChar) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			BaseStatusEffect* FoundStatus = EffectComponent->FindStatusEffect("Drowsy");
			if (FoundStatus && FoundStatus->GetActivateStatus()) return;
			if (AffectedChar->GetCharacterState() == CharacterState::STUN)
				AffectedChar->SetCharacterState(CharacterState::NONE);
		}
	}

}

void StunStatus::ExecuteStatus()
{
	if (AffectedChar) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			FActorSpawnParameters SpawnParams;
			//SpawnParams.Owner = OwningChar;
			StatusEffectActor = AffectedChar->GetWorld()->SpawnActor<AStun>(AStun::StaticClass(), AffectedChar->GetActorLocation(), AffectedChar->GetActorRotation(), SpawnParams);
			if (StatusEffectActor) {
				StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
				StatusEffectActor->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
				//StatusEffectActor->SetActorRelativeScale3D(FVector(2.0f, 1.0f, 2.0f));
				//StunEffect->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
				if (AffectedChar->GetCharacterState() != CharacterState::DEATH) AffectedChar->SetCharacterState(CharacterState::STUN);
				UStatusEffectProgressUI* ProgressUI = EffectComponent->GetProgressUI(this);
				EffectComponent->GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this, EffectComponent, ProgressUI]() {
					if (this && EffectComponent) {
						TimeElapsed += 0.1f;
						if (TimeElapsed >= AffectingTime) {
							EffectComponent->RemoveStatusEffect(this);
							return;
						}
						if (ProgressUI) ProgressUI->GetProgressBar()->SetPercent(GetTimePercentage());
					}
				}), 0.1f, true);
			}
		}
	}
}
