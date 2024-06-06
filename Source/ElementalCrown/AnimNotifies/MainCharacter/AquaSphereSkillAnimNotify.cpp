// Fill out your copyright notice in the Description page of Project Settings.


#include "AquaSphereSkillAnimNotify.h"

void UAquaSphereSkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	USpawnableSkillAnimNotify::OnReceiveNotify_Implementation(OwningInstance);
	/*if (OwningInstance) {
		if (OwningInstance->GetOwningActor()) {
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = BaseCharacter;
				BaseCharacter->GetWorld()->SpawnActor<AAquaSphereProjectile>(AAquaSphereProjectile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			}
		}
	}*/
	SpawnSkillActor<AAquaSphereProjectile>(OwningInstance);
}
