// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTornadoSkillAnimNotify.h"

void UFireTornadoSkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	if (OwningInstance) {
		this->SetSpawnProperty(OwningInstance);
		if (OwningInstance->GetOwningActor()) {
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = BaseCharacter;
				SpawnLocation.Z += 25.00f;
				BaseCharacter->GetWorld()->SpawnActor<AFireTornadoProjectile>(AFireTornadoProjectile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			}
		}
	}
}
