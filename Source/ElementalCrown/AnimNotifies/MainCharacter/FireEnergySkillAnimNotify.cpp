// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEnergySkillAnimNotify.h"

void UFireEnergySkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	if (OwningInstance) {
		this->SetSpawnProperty(OwningInstance);
		if (OwningInstance->GetOwningActor()) {
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = BaseCharacter;
				BaseCharacter->GetWorld()->SpawnActor<AFireEnergyProjectile>(AFireEnergyProjectile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			}
		}
	}
}
