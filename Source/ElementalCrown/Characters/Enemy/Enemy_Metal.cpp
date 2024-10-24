#include "Enemy_Metal.h"

AEnemy_Metal::AEnemy_Metal()
{
	CharacterElement = MakeShared<Metal>();
}

float AEnemy_Metal::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0) {
		int FinalDamage = 0;
		if (CurrentState == CharacterState::DROWSY) {
			FinalDamage = (int)DamageAmount + (int)ceil(MaxHealth * 15.0 / 100.0);
			for (int i = 0; i < StatusList->Num(); ++i) {
				TSharedPtr<BaseStatusEffect> value = (*StatusList)[i];
				if (value->GetStatusName() == "Drowsy") StatusList->RemoveAt(i);
			}
		}
		else FinalDamage = (int)DamageAmount;
		if (IGameplayInterface* CauserInteface = Cast<IGameplayInterface>(DamageCauser)) {
			if (Elemental* CauserElemental = CauserInteface->GetElemental()) {
				if (CauserElemental->GetName().IsEqual("Fire")) FinalDamage += (int)ceil(DamageAmount * 1.5f);
			}
		}
		CurrentHealth = CurrentHealth - FinalDamage;
		if (CurrentHealth <= 0) {
			CurrentState = CharacterState::DEATH;
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
				if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT) {
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
