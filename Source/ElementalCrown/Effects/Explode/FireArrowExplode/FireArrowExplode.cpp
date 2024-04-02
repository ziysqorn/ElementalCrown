// Fill out your copyright notice in the Description page of Project Settings.


#include "FireArrowExplode.h"

AFireArrowExplode::AFireArrowExplode() : AExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/ArrowExplosion/Effect_Explosion_Arrow.Effect_Explosion_Arrow'"))
{
}

void AFireArrowExplode::BeginPlay()
{
	AExplode::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2));
}
