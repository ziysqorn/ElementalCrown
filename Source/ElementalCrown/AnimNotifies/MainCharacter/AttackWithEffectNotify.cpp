#include "AttackWithEffectNotify.h"

UAttackWithEffectNotify::UAttackWithEffectNotify()
{
	this->SetBuff(0);
	BuildupAmount = 10.0f;
}

void UAttackWithEffectNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
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
			if (GetWorld()->SweepMultiByObjectType(Hits, Character->GetActorLocation() + FVector(BoxPosition.X * Character->GetSprite()->GetForwardVector().X), Character->GetActorLocation() + FVector(BoxPosition.X * Character->GetSprite()->GetForwardVector().X, BoxPosition.Y, BoxPosition.Z), FQuat(0, 0, 0, 0), ObjectFilter, FCollisionShape::MakeBox(BoxExtent), AdditionParams)) {
				for (const FHitResult& Result : Hits) {
					TSubclassOf<UDamageType> DamageType;
					this->SpawnImpact(Character, Result.GetComponent()->GetCollisionObjectType(), Result);
					UGameplayStatics::SetGlobalTimeDilation(this, HitStopDilation);
					GetWorld()->GetTimerManager().SetTimer(Character->GetHitStopHandle(), FTimerDelegate::CreateUObject(this, &UAttackAnimNotify::SetHitStopToNormal), HitStopDuration, false);
					UGameplayStatics::ApplyDamage(Result.GetActor(), Character->CalculatedDamage(this->Buff), Character->GetController(), Character, DamageType);
					if (IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(Character)) {
						if (UElemental* CharacterElement = GameplayInterface->GetElemental())
							CharacterElement->ApplyStatusEffect(Cast<ABaseCharacter>(Result.GetActor()), BuildupAmount);
					}
				}
			}
		}
	}
}
