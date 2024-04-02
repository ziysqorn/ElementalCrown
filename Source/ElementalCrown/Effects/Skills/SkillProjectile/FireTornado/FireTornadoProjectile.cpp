// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTornadoProjectile.h"

AFireTornadoProjectile::AFireTornadoProjectile() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/FireTornado/Effect_Skill_FireTornado.Effect_Skill_FireTornado'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 350.00f;
		ProjectileMovement->MaxSpeed = 350.00f;
	}
	this->DestroyDelay = 2.00f;
	OwningSkill = new FireTornadoSkill();
	this->OnActorBeginOverlap.AddDynamic(this, &AFireTornadoProjectile::BeginOverlap);
}

void AFireTornadoProjectile::BeginPlay()
{
	Super::BeginPlay();
	ASkillProjectile::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2.5));
}

void AFireTornadoProjectile::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyDamage(OtherActor, OwningCharacter->CalculatedDamage(OwningSkill->GetSkillDamage()), OwningCharacter->GetController(), this, DamageType);
		}
		if (ABaseCharacter* OtherCharacter = Cast<ABaseCharacter>(OtherActor)) {
			OtherCharacter->LaunchCharacter(FVector(0, 0, 500), false, false);
			OtherCharacter->SetCharacterState(CharacterState::STUNNED);
		}
	}
}
