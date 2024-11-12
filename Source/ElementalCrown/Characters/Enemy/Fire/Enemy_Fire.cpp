#include "Enemy_Fire.h"

AEnemy_Fire::AEnemy_Fire()
{
}

void AEnemy_Fire::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UFire>(this, TEXT("CharacterElement"));
}

float AEnemy_Fire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0) {
		int FinalDamage = (int)DamageAmount;
		if (BaseStatusEffect* Effect = StatusEffectComponent->FindStatusEffect("Drowsy")) {
			if (Effect->GetActivateStatus()) {
				FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
				StatusEffectComponent->RemoveStatusEffect(Effect);
			}
		}
		if (BaseStatusEffect* Effect = StatusEffectComponent->FindStatusEffect("Vulnerable")) {
			if (Effect->GetActivateStatus()) FinalDamage = FinalDamage + (int)ceil(MaxHealth * 10.0f / 100.0f);
		}
		CurrentHealth -= FinalDamage;
		if (CurrentHealth <= 0) {
			StatusEffectComponent->ClearAllStatusEffect();
			CurrentState = CharacterState::DEATH;
			GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
			GetWorldTimerManager().ClearAllTimersForObject(this);
			if (DeathSequence) {
				GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
					TriggerExplosion();
					this->Destroy();
					}), DeathSequence->GetTotalDuration() + 1.50f, false);
			}
		}
		else {
			if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT && CurrentState != CharacterState::STUN && CurrentState != CharacterState::AIRBORNE) {
				ABaseStatus* StatusEffect = Cast<ABaseStatus>(DamageCauser);
				if (!StatusEffect) CurrentState = CharacterState::HURT;
			}
			FlashTimeline.PlayFromStart();
			GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this]() {
				if (this->CurrentState == CharacterState::HURT)
					this->CurrentState = CharacterState::NONE;
				}), 0.2f, false);
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

void AEnemy_Fire::TriggerExplosion()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AFireWispExplode>(AFireWispExplode::StaticClass(), this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
}
