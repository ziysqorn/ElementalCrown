// Fill out your copyright notice in the Description page of Project Settings.


#include "AquilarieArrow.h"
#include "../../../../Effects/Explode/LumberLaunch/LumberLaunchExplode.h"

AAquilarieArrow::AAquilarieArrow() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/AquilarieArrow/Effect_Skill_AquilarieArrow.Effect_Skill_AquilarieArrow'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 500;
		ProjectileMovement->MaxSpeed = 500;
	}
	EffectElement = CreateDefaultSubobject<UPlant>(FName("EffectElement"));
	BuildupAmount = 3.0f;
	this->OnActorBeginOverlap.AddDynamic(this, &AAquilarieArrow::BeginOverlap);
}

void AAquilarieArrow::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<ALumberLaunchExplode>(ALumberLaunchExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}

