// Fill out your copyright notice in the Description page of Project Settings.


#include "VortexPullEffect.h"

AVortexPullEffect::AVortexPullEffect() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/VortexPull/Effect_Skill_VortexPull.Effect_Skill_VortexPull'"))
{
	EffectElement = CreateDefaultSubobject<UPlant>(FName("EffectElement"));
	BuildupAmount = 4.0f;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(-200.0f, 0.0f, 300.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &AVortexPullEffect::BeginOverlap);
}

void AVortexPullEffect::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(3.0f, 1.0f, 2.0f));
}

