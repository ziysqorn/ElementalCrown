// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootAnimNotify.h"

void UShootAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance && OwningInstance->GetOwningActor()) {
		if (APaperZDCharacter* Character = Cast<APaperZDCharacter>(OwningInstance->GetOwningActor())) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Character;
			FVector SpawnLocation = Character->GetSprite()->GetSocketLocation(FName("Arrow"));
			FRotator SpawnRotation = (Character->GetSprite()->GetForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
			AMagicArrow* Arrow = GetWorld()->SpawnActor<AFireArrow>(AFireArrow::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
}
