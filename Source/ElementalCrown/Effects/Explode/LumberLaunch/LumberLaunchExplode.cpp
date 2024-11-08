// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberLaunchExplode.h"
#include "LumberLaunchExplode.h"

ALumberLaunchExplode::ALumberLaunchExplode() : AExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/LumberLaunchExplosion/Effect_Explosion_LumberLaunch.Effect_Explosion_LumberLaunch'"))
{
}

void ALumberLaunchExplode::BeginPlay()
{
	AExplode::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2));
}
