// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTornadoSkillAnimNotify.h"

void UFireTornadoSkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	USpawnableSkillAnimNotify::OnReceiveNotify_Implementation(OwningInstance);
	SpawnLocation.Z += 25.00f;
	SpawnSkillActor<AFireTornadoProjectile>(OwningInstance);
}
