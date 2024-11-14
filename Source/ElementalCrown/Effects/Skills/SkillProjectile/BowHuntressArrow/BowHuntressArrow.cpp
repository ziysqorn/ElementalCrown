// Fill out your copyright notice in the Description page of Project Settings.


#include "BowHuntressArrow.h"
#include "../../../../Effects/Explode/LumberLaunch/LumberLaunchExplode.h"

ABowHuntressArrow::ABowHuntressArrow() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/BowHuntressArrow/Effect_Skill_BowHuntressArrow.Effect_Skill_BowHuntressArrow'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 500;
		ProjectileMovement->MaxSpeed = 500;
	}
	EffectElement = CreateDefaultSubobject<UPlant>(FName("EffectElement"));
	BuildupAmount = 2.0f;
	this->OnActorBeginOverlap.AddDynamic(this, &ABowHuntressArrow::BeginOverlap);
}

void ABowHuntressArrow::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<ALumberLaunchExplode>(ALumberLaunchExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}
