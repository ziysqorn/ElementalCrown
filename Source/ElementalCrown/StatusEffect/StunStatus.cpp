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

	if (IsValid(AffectedChar)) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			UBaseStatusEffect* FoundStatus = EffectComponent->FindStatusEffect("Drowsy");
			if (FoundStatus && FoundStatus->GetActivateStatus()) return;
			if (AffectedChar->GetCharacterState() == CharacterState::STUN)
				AffectedChar->SetCharacterState(CharacterState::NONE);
		}
	}
}

void UStunStatus::ExecuteStatus()
{
	if (IsValid(AffectedChar)) {
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = OwningChar;
		StatusEffectActor = GetWorld()->SpawnActor<AStun>(AStun::StaticClass(), AffectedChar->GetActorLocation(), AffectedChar->GetActorRotation(), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
			StatusEffectActor->SetActorRelativeLocation(FVector(-15.0f, 0.0f, 55.0f));
			//StatusEffectActor->SetActorRelativeScale3D(FVector(2.0f, 1.0f, 2.0f));
			//StunEffect->SetActorRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			if (AffectedChar->GetCharacterState() != CharacterState::DEATH) AffectedChar->SetCharacterState(CharacterState::STUN);
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateUObject(this, &UStunStatus::AffectingCountdown), 0.1f, true);
		}
	}
}
