// Fill out your copyright notice in the Description page of Project Settings.


#include "Punch1AnimNotify.h"

UPunch1AnimNotify::UPunch1AnimNotify()
{
	this->SetBuff();
}

void UPunch1AnimNotify::SetBuff()
{
	this->Buff =  -3;
}

void UPunch1AnimNotify::SpawnImpact(APaperZDCharacter* Character, const ECollisionChannel& OwnerObjectType, const FHitResult& Target) const
{
	FVector ImpactLocation = Target.GetActor()->GetActorLocation();
	FRotator ImpactRotation = (Character->GetActorLocation().X <= ImpactLocation.X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	FActorSpawnParameters SpawnParams;
	ImpactLocation.Y += 1.1;
	SpawnParams.Owner = Character;
	GetWorld()->SpawnActor<APunchImpact>(APunchImpact::StaticClass(), ImpactLocation, ImpactRotation, SpawnParams);
}
