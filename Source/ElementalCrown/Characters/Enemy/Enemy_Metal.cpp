#include "Enemy_Metal.h"

AEnemy_Metal::AEnemy_Metal()
{
	CharacterElement = CreateDefaultSubobject<UMetal>(TEXT("CharacterElement"));
}

float AEnemy_Metal::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0) {
		int FinalDamage = (int)DamageAmount;
		for (int i = 0; i < StatusList->Num(); ++i) {
			if (!IsValid((*StatusList)[i])) continue;
			if ((*StatusList)[i]->GetActivateStatus()) {
				if ((*StatusList)[i]->GetStatusName().IsEqual("Drowsy")) {
					FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
					(*StatusList)[i]->RemoveStatusFromList(i);
				}
				else if ((*StatusList)[i]->GetStatusName().IsEqual("Vulnerable")) {
					FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
				}
			}
		}
		if (IGameplayInterface* CauserInteface = Cast<IGameplayInterface>(DamageCauser)) {
			if (UElemental* CauserElemental = CauserInteface->GetElemental()) {
				if (CauserElemental->GetName().IsEqual("Fire")) FinalDamage += (int)ceil(DamageAmount * 1.5f);
			}
		}
		CurrentHealth = CurrentHealth - FinalDamage;
		if (CurrentHealth <= 0) {
			this->ClearAllStatusEffect();
			CurrentState = CharacterState::DEATH;
			GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
			GetWorldTimerManager().ClearAllTimersForObject(this);
			if (DeathSequence) {
				GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
					this->Destroy();
					}), DeathSequence->GetTotalDuration() + 1.50f, false);
			}
		}
		else {
			FlashTimeline.PlayFromStart();
			if (HurtSequence) {
				if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT && CurrentState != CharacterState::STUN) {
					CurrentState = CharacterState::HURT;
				}
				GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this, EventInstigator]() {
					if (this->CurrentState == CharacterState::HURT) {
						this->CurrentState = CharacterState::NONE;
					}
					if (EventInstigator) {
						FRotator CharacterRotation = (EventInstigator->GetPawn()->GetActorLocation().X > this->GetActorLocation().X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
						this->SetActorRotation(CharacterRotation);
					}
					}), HurtSequence->GetTotalDuration(), false);
			}
		}
		if (StatsPopoutSubclass) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			if (AStatsPopout* stats = GetWorld()->SpawnActor<AStatsPopout>(StatsPopoutSubclass, this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
				if (UStatsPopoutUI* statsUI = stats->GetStatsPopoutUI()) {
					FText inText = FText::FromString(FString::FromInt(FinalDamage));
					statsUI->SetText(inText);
				}
			}
		}
	}
	return 0.0f;
}
