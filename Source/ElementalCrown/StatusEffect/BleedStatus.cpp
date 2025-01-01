#include "BleedStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

UBleedStatus::UBleedStatus()
{
	StatusName = "Bleed";
	AffectingTime = 8.0f;
	TimeForAReset = 0.1f;
}

void UBleedStatus::BeginDestroy()
{
	Super::BeginDestroy();

	if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(ApplyDelayHandle);
}

void UBleedStatus::ExecuteStatus()
{
	if (IsValid(OwningChar) && IsValid(AffectedChar)) {
		UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp();
		GetWorld()->GetTimerManager().SetTimer(ApplyDelayHandle, FTimerDelegate::CreateUObject(this, &UBleedStatus::BloodSoaking), 0.3f, false);
	}
}

void UBleedStatus::BloodSoaking()
{
	if (IsValid(OwningChar) && IsValid(AffectedChar)) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwningChar;
			StatusEffectActor = GetWorld()->SpawnActor<ABleed>(ABleed::StaticClass(), FVector(10.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			if (StatusEffectActor) {
				StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
				TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
				if (DamageType) {
					UGameplayStatics::ApplyDamage(AffectedChar, AffectedChar->GetMaxHealth() * 20 / 100, OwningChar ? OwningChar->GetController() : AffectedChar->GetController(), StatusEffectActor, DamageType);
				}
				EffectComponent->RemoveStatusEffect(this);
			}
		}
	}
}
