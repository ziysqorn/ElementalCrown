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
	if (OwningCharacter && AffectedCharacter) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		StatusEffectActor = AffectedCharacter->GetWorld()->SpawnActor<ABurn>(ABurn::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		if (StatusEffectActor) {
			StatusEffectActor->AttachToActor(AffectedCharacter, FAttachmentTransformRules::KeepRelativeTransform);
			isActivated = true;
			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
				if (OwningCharacter && AffectedCharacter) {
					TSubclassOf<UDamageType> DamageType;
					UGameplayStatics::ApplyDamage(AffectedCharacter, BurnDamage, OwningCharacter->GetController(), OwningCharacter, DamageType);
					TimeElapsed += TimeBetweenEachBurn;
					if (TimeElapsed >= AffectingTime) this->RemoveStatusFromList();
				}
				}), TimeBetweenEachBurn, true);
		}
	}
}


