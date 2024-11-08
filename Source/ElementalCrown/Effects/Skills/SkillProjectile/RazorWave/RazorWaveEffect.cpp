// Fill out your copyright notice in the Description page of Project Settings.


#include "RazorWaveEffect.h"

ARazorWaveEffect::ARazorWaveEffect() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/RazorWave/Effect_Skill_RazorWave.Effect_Skill_RazorWave'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->MaxSpeed = 650;
		ProjectileMovement->InitialSpeed = 650;
		ProjectileMovement->ProjectileGravityScale = 0;
	}
	EffectElement = CreateDefaultSubobject<UMetal>(FName("EffectElement"));
	BuildupAmount = 3.0f;
	this->OnActorBeginOverlap.AddDynamic(this, &ARazorWaveEffect::BeginOverlap);
}

void ARazorWaveEffect::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<ARazorWaveExplode>(ARazorWaveExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}
