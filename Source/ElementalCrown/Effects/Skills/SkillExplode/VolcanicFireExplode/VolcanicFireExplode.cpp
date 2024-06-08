// Fill out your copyright notice in the Description page of Project Settings.


#include "VolcanicFireExplode.h"

AVolcanicFireExplode::AVolcanicFireExplode() : ASkillExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/VolcanicFireExplosion/Effect_Skill_VolcanicFireExplosion.Effect_Skill_VolcanicFireExplosion'"))
{
	this->OnActorBeginOverlap.AddDynamic(this, &AVolcanicFireExplode::BeginOverlap);
	EffectElement = new Fire();
}

void AVolcanicFireExplode::BeginPlay()
{
	ASkillExplode::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2));
	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
	}), this->Flipbook->GetTotalDuration(), false);
}

void AVolcanicFireExplode::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ASkillExplode::BeginOverlap(OverlappedActor, OtherActor);
	if (APaperZDCharacter* OverlappedCharacter = Cast<APaperZDCharacter>(OtherActor)) 
		OverlappedCharacter->LaunchCharacter(FVector(0, 0, 300), false, false);
}
