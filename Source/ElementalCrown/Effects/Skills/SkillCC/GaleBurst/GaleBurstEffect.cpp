// Fill out your copyright notice in the Description page of Project Settings.


#include "GaleBurstEffect.h"

AGaleBurstEffect::AGaleBurstEffect() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/GaleBurst/Effect_Skill_GaleBurst.Effect_Skill_GaleBurst'"))
{
	EffectElement = CreateDefaultSubobject<UPlant>(FName("EffectElement"));
	BuildupAmount = 4.0f;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(300.0f, 0.0f, 300.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &AGaleBurstEffect::BeginOverlap);
}

void AGaleBurstEffect::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(3.0f, 1.0f, 2.0f));
}
