// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTornadoProjectile.h"

AFireTornadoProjectile::AFireTornadoProjectile() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/FireTornado/Effect_Skill_FireTornado.Effect_Skill_FireTornado'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 350.00f;
		ProjectileMovement->MaxSpeed = 350.00f;
	}
	this->DestroyDelay = 2.00f;
	EffectElement = new Fire();
	this->OnActorBeginOverlap.AddDynamic(this, &AFireTornadoProjectile::BeginOverlap);
}

void AFireTornadoProjectile::BeginPlay()
{
	Super::BeginPlay();
	ASkillProjectile::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2.5));
}
