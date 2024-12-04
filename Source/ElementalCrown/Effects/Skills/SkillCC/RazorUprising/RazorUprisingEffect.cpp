// Fill out your copyright notice in the Description page of Project Settings.


#include "RazorUprisingEffect.h"

ARazorUprisingEffect::ARazorUprisingEffect() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/RazorUprising/Effect_Skill_RazorUprising.Effect_Skill_RazorUprising'"))
{
	EffectElement = CreateDefaultSubobject<UMetal>(FName("EffectElement"));
	BuildupAmount = 4.0f;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(300.0f, 0.0f, 300.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &ARazorUprisingEffect::BeginOverlap);
}

void ARazorUprisingEffect::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(2.0f, 1.0f, 1.5f));
}
