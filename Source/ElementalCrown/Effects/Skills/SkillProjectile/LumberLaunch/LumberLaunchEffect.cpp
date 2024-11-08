// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberLaunchEffect.h"

ALumberLaunchEffect::ALumberLaunchEffect() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/LumberLaunch/Effect_Skill_LumberLaunch.Effect_Skill_LumberLaunch'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->MaxSpeed = 650;
		ProjectileMovement->InitialSpeed = 650;
		ProjectileMovement->ProjectileGravityScale = 0;
	}
	EffectElement = CreateDefaultSubobject<UPlant>(FName("EffectElement"));
	BuildupAmount = 5.0f;
	this->OnActorBeginOverlap.AddDynamic(this, &ALumberLaunchEffect::BeginOverlap);
}

void ALumberLaunchEffect::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<ALumberLaunchExplode>(ALumberLaunchExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}