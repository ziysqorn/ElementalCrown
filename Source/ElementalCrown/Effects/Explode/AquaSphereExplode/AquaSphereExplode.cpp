// Fill out your copyright notice in the Description page of Project Settings.


#include "AquaSphereExplode.h"

AAquaSphereExplode::AAquaSphereExplode() : AExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/AquaSphereExplosion/Effect_Explosion_AquaSphere.Effect_Explosion_AquaSphere'"))
{
}

void AAquaSphereExplode::BeginPlay()
{
	AExplode::BeginPlay();
	this->SetActorScale3D(FVector(1.5, 1, 1.5));
}
