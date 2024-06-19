// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
 	if (FlashCurveFloat) {
		FlashTimeline.AddInterpFloat(FlashCurveFloat, FOnTimelineFloatStatic::CreateLambda([this](const float& Value) {
			UMaterialInstanceDynamic* DynamicMaterial = this->GetSprite()->CreateDynamicMaterialInstance(0);
			DynamicMaterial->SetScalarParameterValue("FlashMultiplier", Value);
		}));
	}
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FlashTimeline.TickTimeline(DeltaSeconds);
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentState != CharacterState::HURT && CurrentState != CharacterState::DEATH)
	{
		if (CurrentHealth > 0) {
			CurrentHealth -= (int)DamageAmount;
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
				CurrentState = CharacterState::HURT;
				FlashTimeline.PlayFromStart();
				if (HurtSequence) {
					GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateLambda([this]() {
						if (this->CurrentState == CharacterState::HURT)
							this->CurrentState = CharacterState::NONE;
						}), HurtSequence->GetTotalDuration(), false);
				}
			}
			if (StatsPopoutSubclass) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				if (AStatsPopout* stats = GetWorld()->SpawnActor<AStatsPopout>(StatsPopoutSubclass, this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
					if (UStatsPopoutUI* statsUI = stats->GetStatsPopoutUI()) {
						FText inText = FText::FromString(FString::FromInt((int)DamageAmount));
						statsUI->SetText(inText);
					}
				}
			}
		}
	}
	return 0.0f;
}
