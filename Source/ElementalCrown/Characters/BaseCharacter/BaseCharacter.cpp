// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	StatusList = MakeShared<TArray<UBaseStatusEffect*>>();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
 	if (FlashCurveFloat) {
		FlashTimeline.AddInterpFloat(FlashCurveFloat, FOnTimelineFloatStatic::CreateLambda([this](const float& Value) {
			UMaterialInstanceDynamic* DynamicMaterial = this->GetSprite()->CreateDynamicMaterialInstance(0);
			DynamicMaterial->SetScalarParameterValue("FlashMultiplier", Value);
		}));
	}
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FlashTimeline.TickTimeline(DeltaSeconds);
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
		CurrentHealth -= FinalDamage;
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
					FText inText = FText::FromString(FString::FromInt(FinalDamage));
					statsUI->SetText(inText);
				}
			}
		}
	}
	return 0.0f;
}
