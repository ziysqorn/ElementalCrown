// Fill out your copyright notice in the Description page of Project Settings.


#include "FireSlashWaveExplode.h"

AFireSlashWaveExplode::AFireSlashWaveExplode() : AExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/FireExplosion/Effect_Skill_TempFireExplode.Effect_Skill_TempFireExplode'"))
{
}

void AFireSlashWaveExplode::BeginPlay()
{
	AExplode::BeginPlay();
	//Set this actor's size;
	this->SetActorScale3D(FVector(1.25, 1, 1.25));
}
