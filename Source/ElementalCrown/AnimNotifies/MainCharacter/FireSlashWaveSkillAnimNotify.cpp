// Fill out your copyright notice in the Description page of Project Settings.

#include "FireSlashWaveSkillAnimNotify.h"

void UFireSlashWaveSkillAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	USpawnableSkillAnimNotify::OnReceiveNotify_Implementation(OwningInstance);
	SpawnSkillActor<AFireSlashWave>(OwningInstance);
}
