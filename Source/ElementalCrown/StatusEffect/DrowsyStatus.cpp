#include "DrowsyStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

DrowsyStatus::DrowsyStatus()
{
	StatusName = "Drowsy";
	AffectingTime = 3.0f;
	TimeForAReset = 0.2f;
}

DrowsyStatus::~DrowsyStatus()
{
	if (AffectedChar) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			if (EffectComponent->FindStatusEffect("Stun")) return;
			if (AffectedChar->GetCharacterState() != CharacterState::DEATH)
				AffectedChar->SetCharacterState(CharacterState::NONE);
		}
	}
}

void DrowsyStatus::ExecuteStatus()
{
	if (OwningChar && AffectedChar) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwningChar;
			StatusEffectActor = AffectedChar->GetWorld()->SpawnActor<ADrowsy>(ADrowsy::StaticClass(), AffectedChar->GetActorLocation(), AffectedChar->GetActorRotation(), SpawnParams);
			if (StatusEffectActor) {
				StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
				StatusEffectActor->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
				StatusEffectActor->SetActorRelativeScale3D(FVector(2.0f, 0.0f, 2.0f));
				StatusEffectActor->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
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
