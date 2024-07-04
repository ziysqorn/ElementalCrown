// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotify.h"


UAttackAnimNotify::UAttackAnimNotify()
{
	this->SetBuff(0);
}

void UAttackAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance && OwningInstance->GetOwningActor()) {
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
			DrawDebugBox(GetWorld(), Character->GetActorLocation() + FVector(BoxPosition.X * Character->GetSprite()->GetForwardVector().X, BoxPosition.Y, BoxPosition.Z), BoxExtent, FColor::Purple, false, 2);
			TArray<FHitResult> Hits;
			FCollisionObjectQueryParams ObjectFilter;
			FCollisionQueryParams AdditionParams;
			ObjectFilter.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
			ObjectFilter.AddObjectTypesToQuery(ECollisionChannel::ECC_Destructible);
		    AdditionParams.AddIgnoredActor(Character);
			if (GetWorld()->SweepMultiByObjectType(Hits, Character->GetActorLocation() + FVector(BoxPosition.X * Character->GetSprite()->GetForwardVector().X), Character->GetActorLocation() + FVector(BoxPosition.X*Character->GetSprite()->GetForwardVector().X, BoxPosition.Y, BoxPosition.Z), FQuat(0, 0, 0, 0), ObjectFilter, FCollisionShape::MakeBox(BoxExtent), AdditionParams)) {
				for (const FHitResult& Result : Hits) {
					TSubclassOf<UDamageType> DamageType;
					this->SpawnImpact(Character, Result.GetComponent()->GetCollisionObjectType(), Result);
					UGameplayStatics::ApplyDamage(Result.GetActor(), Character->CalculatedDamage(this->Buff), Character->GetController(), Character, DamageType);
					if (ABaseCharacter* AffectedCharacter = Cast<ABaseCharacter>(Result.GetActor())) {
						Elemental* CharacterElemental = Character->GetCharacterElemental();
						CharacterElemental->ApplyStatusEffect(AffectedCharacter);
					}
				}
			}
		}
	}
}

void UAttackAnimNotify::SpawnImpact(APaperZDCharacter* Character, const ECollisionChannel& OwnerObjectType, const FHitResult& Target) const
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


