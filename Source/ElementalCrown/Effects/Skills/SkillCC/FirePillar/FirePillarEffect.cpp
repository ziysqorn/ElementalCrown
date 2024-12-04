// Fill out your copyright notice in the Description page of Project Settings.


#include "FirePillarEffect.h"
#include "../../../Explode/FireEnergyExplode/FireEnergyExplode.h"

AFirePillarEffect::AFirePillarEffect() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/FirePillar/Effect_Skill_FirePillar.Effect_Skill_FirePillar'"))
{
	EffectElement = CreateDefaultSubobject<UFire>(FName("EffectElement"));
	BuildupAmount = 10.0f;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(500.0f, 0.0f, 100.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &AFirePillarEffect::BeginOverlap);
}

void AFirePillarEffect::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(3, 1, 4));
}