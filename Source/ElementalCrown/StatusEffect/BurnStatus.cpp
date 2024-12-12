// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

BurnStatus::BurnStatus()
{
	StatusName = "Burn";
	AffectingTime = 4.0f;
	TimeForAReset = 0.3f;
}

void BurnStatus::ExecuteStatus()
{
	if (AffectedChar) {
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = OwningChar;
		StatusEffectActor = AffectedChar->GetWorld()->SpawnActor<ABurn>(ABurn::StaticClass(), FVector(0.0f, 0.0f, 5.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);

			UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp();
			UStatusEffectProgressUI* ProgressUI = EffectComponent->GetProgressUI(this);
			EffectComponent->GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this, EffectComponent, ProgressUI]() {
				if (this && AffectedChar && EffectComponent) {
					TSubclassOf<UDamageType> DamageType;
					UGameplayStatics::ApplyDamage(AffectedChar, BurnDamage, OwningChar ? OwningChar->GetController() : AffectedChar->GetController(), StatusEffectActor, DamageType);
					TimeElapsed += TimeBetweenEachBurn;
					if (TimeElapsed >= AffectingTime) {
						EffectComponent->RemoveStatusEffect(this);
						return;
					}
					if(ProgressUI) ProgressUI->GetProgressBar()->SetPercent(GetTimePercentage());
				}
				else {
					EffectComponent->RemoveStatusEffect(this);
					return;
				}
				}), TimeBetweenEachBurn, true);
		}
	}
}


