// Fill out your copyright notice in the Description page of Project Settings.


#include "EarthshatterUpliftEffect.h"

AEarthshatterUpliftEffect::AEarthshatterUpliftEffect() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/EarthshatterUplift/Effect_Skill_EarthshatterUplift.Effect_Skill_EarthshatterUplift'"))
{
	EffectElement = CreateDefaultSubobject<UEarth>(FName("EffectElement"));
	BuildupAmount = 4.0f;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(0.0f, 0.0f, 400.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &AEarthshatterUpliftEffect::BeginOverlap);
}

void AEarthshatterUpliftEffect::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(3.0f, 1.0f, 2.5f));
}
