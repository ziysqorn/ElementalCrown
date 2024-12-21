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

	if (!DetectingPlayer() && !DetectingPatrolLimit()) GetCharacterMovement()->MaxWalkSpeed = BaseEnemySpeed;
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
			this->Dead();
			return;
		}
	}), 1.0f, true);
}

