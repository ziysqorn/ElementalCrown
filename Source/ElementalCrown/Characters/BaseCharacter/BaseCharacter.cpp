// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	StatusEffectComponent = CreateDefaultSubobject<UStatusEffectComponent>(TEXT("StatusEffectComponent"));
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
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
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
					this->Destroy();
					}), DeathSequence->GetTotalDuration() + 1.50f, false);
			}
		}
		else {
			ABaseStatus* StatusEffect = Cast<ABaseStatus>(DamageCauser);
			if(!StatusEffect) CurrentState = CharacterState::HURT;
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
