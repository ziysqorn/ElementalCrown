// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneBarrageEffect.h"

AStoneBarrageEffect::AStoneBarrageEffect() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/StoneBarrage/Effect_Skill_StoneBarrage.Effect_Skill_StoneBarrage'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->MaxSpeed = 650;
		ProjectileMovement->InitialSpeed = 650;
		ProjectileMovement->ProjectileGravityScale = 0;
	}
	EffectElement = CreateDefaultSubobject<UEarth>(FName("EffectElement"));
	BuildupAmount = 2.0f;
	this->OnActorBeginOverlap.AddDynamic(this, &AStoneBarrageEffect::BeginOverlap);
}

void AStoneBarrageEffect::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AStoneBarrageExplode>(AStoneBarrageExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}