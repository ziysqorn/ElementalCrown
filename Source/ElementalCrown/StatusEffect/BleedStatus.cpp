#include "BleedStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

BleedStatus::BleedStatus()
{
	StatusName = "Bleed";
	AffectingTime = 8.0f;
	TimeForAReset = 0.1f;
}

void BleedStatus::ExecuteStatus()
{
	if (AffectedChar) {
		UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp();
		EffectComponent->GetWorld()->GetTimerManager().SetTimer(ApplyDelayHandle, FTimerDelegate::CreateLambda([this, EffectComponent]() {
			if (this && EffectComponent && AffectedChar) {
				FActorSpawnParameters SpawnParams;
				//SpawnParams.Owner = OwningChar;
				if (ABleed* BleedEffect = AffectedChar->GetWorld()->SpawnActor<ABleed>(ABleed::StaticClass(), FVector(10.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
					BleedEffect->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
					TSubclassOf<UDamageType> DamageType;
					UGameplayStatics::ApplyDamage(AffectedChar, AffectedChar->GetMaxHealth() * 20 / 100, OwningChar ? OwningChar->GetController() : AffectedChar->GetController(), BleedEffect, DamageType);
					EffectComponent->RemoveStatusEffect(this);
				}
			}
		}), 0.3f, false);
	}
}
