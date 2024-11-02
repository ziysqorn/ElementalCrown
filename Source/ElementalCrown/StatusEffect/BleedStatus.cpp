#include "BleedStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

UBleedStatus::UBleedStatus()
{
	StatusName = "Bleed";
	AffectingTime = 8.0f;
	TimeForAReset = 0.1f;
}

void UBleedStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		if (ABleed* BleedEffect = AffectedCharacter->GetWorld()->SpawnActor<ABleed>(ABleed::StaticClass(), AffectedCharacter->GetActorLocation(), AffectedCharacter->GetActorRotation(), SpawnParams)) {
			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyDamage(AffectedCharacter, AffectedCharacter->GetMaxHealth() * 20 / 100, OwningCharacter->GetController(), OwningCharacter, DamageType);
			this->RemoveStatusFromList();
		}
	}
}
