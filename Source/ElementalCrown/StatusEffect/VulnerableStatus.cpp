#include "VulnerableStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

UVulnerableStatus::UVulnerableStatus()
{
	StatusName = "Vulnerable";
	AffectingTime = 10.0f;
	TimeForAReset = 0.2f;
}

void UVulnerableStatus::ExecuteStatus()
{
	if (IsValid(AffectedChar)) {
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = OwningChar;
		StatusEffectActor = GetWorld()->SpawnActor<AVulnerable>(AVulnerable::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateUObject(this, &UVulnerableStatus::AffectingCountdown), 0.1f, true);
		}
	}
}
