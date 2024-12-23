// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTornadoProjectile.h"

AFireTornadoProjectile::AFireTornadoProjectile() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/FireTornado/Effect_Skill_FireTornado.Effect_Skill_FireTornado'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 350.00f;
		ProjectileMovement->MaxSpeed = 350.00f;
	}
	this->DestroyDelay = 2.00f;
	this->BuildupAmount = 10.0f;
	SkillDamage = 5;
	EffectElement = CreateDefaultSubobject<UFire>(FName("EffectElement"));
	this->OnActorBeginOverlap.AddDynamic(this, &AFireTornadoProjectile::BeginOverlap);
}

void AFireTornadoProjectile::BeginPlay()
{
	ASkillProjectile::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2.5));
}

void AFireTornadoProjectile::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && this->GetOwner() && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			if (EffectElement) {
				if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor)) {
					ABossCharacter* BossCharacter = Cast<ABossCharacter>(Character);
					if (!BossCharacter) {
						Character->GetMovementComponent()->StopMovementImmediately();
						if (Character->GetCharacterState() != CharacterState::STUN)
							Character->SetCharacterState(CharacterState::AIRBORNE);
						Character->LaunchCharacter(FVector(0.0f, 0, 500.0f), true, true);
					}
					UGameplayStatics::ApplyDamage(OtherActor, OwningCharacter->CalculatedDamage(SkillDamage), OwningCharacter->GetController(), this, DamageType);
					EffectElement->ApplyStatusEffect(Character, BuildupAmount);
				}
			}
		}
	}
}
