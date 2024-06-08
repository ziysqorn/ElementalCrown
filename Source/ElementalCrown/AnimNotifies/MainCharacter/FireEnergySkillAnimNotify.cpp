// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEnergySkillAnimNotify.h"

void UFireEnergySkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	USpawnableSkillAnimNotify::OnReceiveNotify_Implementation(OwningInstance);
	SpawnSkillActor<AFireEnergyProjectile>(OwningInstance);
}
