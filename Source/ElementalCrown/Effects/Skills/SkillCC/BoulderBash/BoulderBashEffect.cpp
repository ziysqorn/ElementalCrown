// Fill out your copyright notice in the Description page of Project Settings.


#include "BoulderBashEffect.h"

ABoulderBashEffect::ABoulderBashEffect() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/BoulderBash/Effect_Skill_BoulderBash.Effect_Skill_BoulderBash'"))
{
	EffectElement = CreateDefaultSubobject<UEarth>(FName("EffectElement"));
	BuildupAmount = 4.0f;
	SkillDamage = 5;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(300.0f, 0.0f, 300.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &ABoulderBashEffect::BeginOverlap);
}

void ABoulderBashEffect::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorScale3D(FVector(3.0f, 1.0f, 2.5f));
}