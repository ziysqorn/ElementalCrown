// Fill out your copyright notice in the Description page of Project Settings.


#include "AirSlash3EndAnimNotifyState.h"

void UAirSlash3EndAnimNotifyState::SpawnImpact(APaperZDCharacter* Character, const ECollisionChannel& OwnerObjectType, const FHitResult& Target)
{
	FVector ImpactLocation = Target.GetActor()->GetActorLocation();
	FRotator ImpactRotation = (Character->GetActorLocation().X <= ImpactLocation.X) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	FActorSpawnParameters SpawnParams;
	ImpactLocation.Y += 1.1;
	SpawnParams.Owner = Character;
		switch (OwnerObjectType) {
		case ECollisionChannel::ECC_Pawn:
			GetWorld()->SpawnActor<ABloodSlashImpact>(ABloodSlashImpact::StaticClass(), ImpactLocation, ImpactRotation, SpawnParams);
			break;
		case ECollisionChannel::ECC_Destructible:
			GetWorld()->SpawnActor<ANoBloodSlashImpact>(ANoBloodSlashImpact::StaticClass(), ImpactLocation, ImpactRotation, SpawnParams);
			break;
		}
}

void UAirSlash3EndAnimNotifyState::SetBuff()
{
	this->Buff = 5;
}

void UAirSlash3EndAnimNotifyState::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	if (OwningInstance && OwningInstance->GetOwningActor()) {
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
			DrawDebugBox(GetWorld(), Character->GetActorLocation(), BoxExtent, FColor::Purple, false, 2);
			TArray<FHitResult> Hits;
			FCollisionObjectQueryParams ObjectFilter;
			FCollisionQueryParams AdditionParams;
			ObjectFilter.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
			ObjectFilter.AddObjectTypesToQuery(ECollisionChannel::ECC_Destructible);
			AdditionParams.AddIgnoredActor(Character);
			if (GetWorld()->SweepMultiByObjectType(Hits, Character->GetActorLocation(), Character->GetActorLocation(), FQuat(0, 0, 0, 0), ObjectFilter, FCollisionShape::MakeBox(BoxExtent), AdditionParams)) {
				for (const FHitResult& Result : Hits) {
					UAirSlash3EndAnimNotifyState::SpawnImpact(Character, Result.GetComponent()->GetCollisionObjectType(), Result);
					TSubclassOf<UDamageType> DamageType;
					this->SetBuff();
					UGameplayStatics::ApplyDamage(Result.GetActor(), Character->CalculatedDamage(Buff), Character->GetController(), Character, DamageType);
				}
			}
		}
	}
}

void UAirSlash3EndAnimNotifyState::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance)
{
}
