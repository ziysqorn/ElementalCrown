// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_FireWisp.h"

AEnemy_FireWisp::AEnemy_FireWisp()
{
	MaxHealth = 15;
	CurrentHealth = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = BaseEnemySpeed;
}

void AEnemy_FireWisp::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!DetectingPlayer() && !DetectingWall()) GetCharacterMovement()->MaxWalkSpeed = BaseEnemySpeed;
	else if (DetectingPlayer()) {
		GetCharacterMovement()->MaxWalkSpeed = BaseEnemySpeed * 2.0f;
		PlayerDetectBox.X = 500.0f;
		PlayerDetectBox.Z = 1000.0f;
		if (!isCountdowning) SelfDestroy();
	}
	this->Move();
}

bool AEnemy_FireWisp::DetectingPlayer()
{
	FHitResult PlayerDetectResult;
	FCollisionObjectQueryParams DetectObjectsParams(ECollisionChannel::ECC_Pawn);
	FCollisionQueryParams DetectParams;
	DetectParams.AddIgnoredActor(this);
	DrawDebugBox(GetWorld(), this->GetActorLocation(), PlayerDetectBox, FColor::Blue);
	bool PlayerDetected = GetWorld()->SweepSingleByObjectType(PlayerDetectResult, this->GetActorLocation(), this->GetActorLocation(), FQuat(0, 0, 0, 0), DetectObjectsParams, FCollisionShape::MakeBox(PlayerDetectBox), DetectParams);
	if (PlayerDetected) {
		FRotator CharacterRotation = (PlayerDetectResult.GetActor()->GetActorLocation().X > this->GetActorLocation().X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
		ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(PlayerDetectResult.GetActor());
		if (!Enemy) {
			if (abs(PlayerDetectResult.GetActor()->GetActorLocation().X - this->GetActorLocation().X) >= 30 && CurrentState != CharacterState::HURT && CurrentState != CharacterState::DEATH && CurrentState != CharacterState::ATTACK)
				this->SetActorRotation(CharacterRotation);
			return true;
		}
	}
	return false;
}

void AEnemy_FireWisp::SelfDestroy()
{
	isCountdowning = true;
	GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda([this]() {
		if (DeathCountdown > 0 && StatsPopoutSubclass) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			if (AStatsPopout* stats = GetWorld()->SpawnActor<AStatsPopout>(StatsPopoutSubclass, this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
				stats->setDistanceX(0.0f);
				if (UStatsPopoutUI* statsUI = stats->GetStatsPopoutUI()) {
					FText inText = FText::FromString(FString::FromInt(DeathCountdown));
					statsUI->SetText(inText);
					statsUI->SetTextColor(FLinearColor::Yellow);
				}
			}
		}
		DeathCountdown -= 1;
		if (DeathCountdown < 0) {
			GetWorldTimerManager().ClearTimer(DeathHandle);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			GetWorld()->SpawnActor<AFireWispExplode>(AFireWispExplode::StaticClass(), this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			this->Destroy();
			return;
		}
	}), 1.0f, true);
}

float AEnemy_FireWisp::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
			TriggerExplosion();
			this->Destroy();
		}
		else {
			if (CurrentState != CharacterState::ATTACK && CurrentState != CharacterState::HURT && CurrentState != CharacterState::STUN && CurrentState != CharacterState::AIRBORNE) {
				ABaseStatus* StatusEffect = Cast<ABaseStatus>(DamageCauser);
				if (!StatusEffect) CurrentState = CharacterState::HURT;
			}
			FlashTimeline.PlayFromStart();
			GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this, EventInstigator]() {
				if (this->CurrentState == CharacterState::HURT)
					this->CurrentState = CharacterState::NONE;
				if (EventInstigator) {
					FRotator CharacterRotation = (EventInstigator->GetPawn()->GetActorLocation().X > this->GetActorLocation().X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
					this->SetActorRotation(CharacterRotation);
				}
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
