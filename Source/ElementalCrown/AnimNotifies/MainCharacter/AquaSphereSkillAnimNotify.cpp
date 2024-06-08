// Fill out your copyright notice in the Description page of Project Settings.


#include "AquaSphereSkillAnimNotify.h"

void UAquaSphereSkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	USpawnableSkillAnimNotify::OnReceiveNotify_Implementation(OwningInstance);
	SpawnSkillActor<AAquaSphereProjectile>(OwningInstance);
}
