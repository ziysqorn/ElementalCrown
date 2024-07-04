// Fill out your copyright notice in the Description page of Project Settings.


#include "VolcanicFireSlashAnimNotify.h"

void UVolcanicFireSlashAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	USpawnableSkillAnimNotify::OnReceiveNotify_Implementation(OwningInstance);
	if (OwningInstance) {
		this->SpawnDistanceX = 50.0f;
		if (OwningInstance->GetOwningActor()) {
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
				this->SpawnContinuously(BaseCharacter);
			}
		}
	}
}

void UVolcanicFireSlashAnimNotify::SpawnContinuously(ABaseCharacter* OwningCharacter) const
{
	if (OwningCharacter) {
		if (CurrentSpawnTime <= MaxSpawnTimes) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwningCharacter;
			SpawnLocation.X += (SpawnRotation.Yaw != 0) ? -SpawnDistanceX : SpawnDistanceX;
			if (AVolcanicFireExplode* VolcanicFireExplode = GetWorld()->SpawnActor<AVolcanicFireExplode>(AVolcanicFireExplode::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams))
				GetWorld()->GetTimerManager().SetTimer(SpawnHandle, FTimerDelegate::CreateLambda([this, OwningCharacter]() {
				this->SpawnContinuously(OwningCharacter);
					}), VolcanicFireExplode->Flipbook->GetTotalDuration(), false);
			++CurrentSpawnTime;
		}
		else CurrentSpawnTime = 1;
	}
}
