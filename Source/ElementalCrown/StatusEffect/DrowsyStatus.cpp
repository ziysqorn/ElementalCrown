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

	if (IsValid(AffectedChar)) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			UBaseStatusEffect* FoundStatus = EffectComponent->FindStatusEffect("Stun");
			if (FoundStatus && FoundStatus->GetActivateStatus()) return;
			if (AffectedChar->GetCharacterState() == CharacterState::STUN)
				AffectedChar->SetCharacterState(CharacterState::NONE);
		}
	}
}

void UDrowsyStatus::ExecuteStatus()
{
	if (IsValid(OwningChar) && IsValid(AffectedChar)) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningChar;
		StatusEffectActor = GetWorld()->SpawnActor<ADrowsy>(ADrowsy::StaticClass(), AffectedChar->GetActorLocation(), AffectedChar->GetActorRotation(), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
			StatusEffectActor->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
			//StatusEffectActor->SetActorRelativeScale3D(FVector(2.0f, 1.0f, 2.0f));
			StatusEffectActor->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			if (AffectedChar->GetCharacterState() != CharacterState::DEATH) AffectedChar->SetCharacterState(CharacterState::STUN);
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateUObject(this, &UDrowsyStatus::AffectingCountdown), 0.1f, true);
		}
	}
}
