// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillCCEffect.h"

ASkillCCEffect::ASkillCCEffect()
{

}

ASkillCCEffect::ASkillCCEffect(const TCHAR* Ref) : ASkillEffect(Ref)
{

}

void ASkillCCEffect::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateUObject(this, &ASkillCCEffect::SelfDestroy), Flipbook->GetTotalDuration(), false);
}

void ASkillCCEffect::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && this->GetOwner() && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			if (EffectElement) {
				if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor)) {
					int BackwardDir = Character->GetActorRotation().Yaw == 0.0f ? -1 : 1;
					LaunchVector.X *= BackwardDir;
					ABossCharacter* BossCharacter = Cast<ABossCharacter>(Character);
					if (!BossCharacter) {
						Character->GetMovementComponent()->StopMovementImmediately();
						if (Character->GetCharacterState() != CharacterState::STUN)
							Character->SetCharacterState(CharacterState::AIRBORNE);
						Character->LaunchCharacter(LaunchVector, true, true);
					}
					UGameplayStatics::ApplyDamage(Character, OwningCharacter->CalculatedDamage(SkillDamage), OwningCharacter->GetController(), this, DamageType);
					EffectElement->ApplyStatusEffect(Character, BuildupAmount);
				}
			}
		}
	}
}

void ASkillCCEffect::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	this->Destroy();
}
