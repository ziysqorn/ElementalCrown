#include "VulnerableStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

VulnerableStatus::VulnerableStatus()
{
	StatusName = "Vulnerable";
	AffectingTime = 2.0f;
	TimeForAReset = 0.2f;
}

void VulnerableStatus::ExecuteStatus()
{
	if (OwningChar && AffectedChar) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwningChar;
			StatusEffectActor = AffectedChar->GetWorld()->SpawnActor<AVulnerable>(AVulnerable::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			if (StatusEffectActor) {
				StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
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
