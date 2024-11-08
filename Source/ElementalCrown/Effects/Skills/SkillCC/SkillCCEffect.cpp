// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillCCEffect.h"

ASkillCC::ASkillCC()
{

}

ASkillCC::ASkillCC(const TCHAR* Ref) : ASkillEffect(Ref)
{

}

void ASkillCC::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
		}), Flipbook->GetTotalDuration(), false);
}

void ASkillCC::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && this->GetOwner() && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			if (EffectElement) {
				if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor)) {
					int BackwardDir = Character->GetActorRotation().Yaw == 0.0f ? -1 : 1;
					LaunchVector.X *= BackwardDir;
					Character->GetMovementComponent()->StopMovementImmediately();
					if(Character->GetCharacterState() != CharacterState::STUN) 
						Character->SetCharacterState(CharacterState::AIRBORNE);
					Character->LaunchCharacter(LaunchVector, true, true);
					UGameplayStatics::ApplyDamage(Character, SkillDamage, OwningCharacter->GetController(), this, DamageType);
					EffectElement->ApplyStatusEffect(Character, BuildupAmount);
				}
			}
		}
	}
}

void ASkillCC::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	this->Destroy();
}
