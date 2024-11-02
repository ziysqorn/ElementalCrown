// Fill out your copyright notice in the Description page of Project Settings.


#include "AquaSphereProjectile.h"

AAquaSphereProjectile::AAquaSphereProjectile() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/AquaSphere/Effect_Skill_AquaSphere.Effect_Skill_AquaSphere'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 500;
		ProjectileMovement->MaxSpeed = 500;
	}
	EffectElement = CreateDefaultSubobject<UWater>(FName("EffectElement"));
	BuildupAmount = 10.0f;
	FlipbookComponent->SetLooping(false);
	this->OnActorBeginOverlap.AddDynamic(this, &AAquaSphereProjectile::BeginOverlap);
	FlipbookComponent->OnFinishedPlaying.AddDynamic(this, &AAquaSphereProjectile::SetLoopAtRightPos);
}

void AAquaSphereProjectile::BeginPlay()
{
	ASkillProjectile::BeginPlay();
	this->SetActorScale3D(FVector(1.75, 1, 1.75));
}

void AAquaSphereProjectile::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AAquaSphereExplode>(AAquaSphereExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}

void AAquaSphereProjectile::SetLoopAtRightPos()
{
	FlipbookComponent->SetPlaybackPositionInFrames(6, true);
	FlipbookComponent->Play();
}
