#include "VulnerableStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

UVulnerableStatus::UVulnerableStatus()
{
	StatusName = "Vulnerable";
	AffectingTime = 2.0f;
	TimeForAReset = 0.2f;
}

void UVulnerableStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		StatusEffectActor = AffectedCharacter->GetWorld()->SpawnActor<AVulnerable>(AVulnerable::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
				TimeElapsed += 0.1f;
				if (TimeElapsed >= AffectingTime) this->RemoveStatusFromList();
				}), 0.1f, true);
		}
	}
}
