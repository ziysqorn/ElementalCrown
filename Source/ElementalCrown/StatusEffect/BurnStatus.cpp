// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

UBurnStatus::UBurnStatus()
{
	StatusName = "Burn";
	AffectingTime = 4.0f;
	TimeForAReset = 0.3f;
}

void UBurnStatus::ExecuteStatus()
{
	if (IsValid(AffectedChar)) {
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = OwningChar;
		StatusEffectActor = GetWorld()->SpawnActor<ABurn>(ABurn::StaticClass(), FVector(0.0f, 0.0f, 5.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedChar, FAttachmentTransformRules::KeepRelativeTransform);
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateUObject(this, &UBurnStatus::Burn), TimeBetweenEachBurn, true);
		}
	}
}

void UBurnStatus::Burn()
{
	if (IsValid(AffectedChar) && IsValid(StatusEffectActor)) {
		if (UStatusEffectComponent* EffectComponent = AffectedChar->GetStatusEffectComp()) {
			TimeElapsed += TimeBetweenEachBurn;
			if (TimeElapsed >= AffectingTime) {
				EffectComponent->RemoveStatusEffect(this);
				return;
			}
			TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
			if (DamageType) {
				UGameplayStatics::ApplyDamage(AffectedChar, BurnDamage, IsValid(OwningChar) ? OwningChar->GetController() : AffectedChar->GetController(), StatusEffectActor, DamageType);
			}
			if (UStatusEffectProgressUI* ProgressUI = EffectComponent->GetProgressUI(this)) 
				ProgressUI->GetProgressBar()->SetPercent(GetTimePercentage());
		}
	}
}


