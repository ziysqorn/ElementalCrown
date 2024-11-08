// Fill out your copyright notice in the Description page of Project Settings.


#include "RazorWaveExplode.h"

ARazorWaveExplode::ARazorWaveExplode() : AExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/RazorWaveExplosion/Effect_Explosion_RazorWave.Effect_Explosion_RazorWave'"))
{

}

void ARazorWaveExplode::BeginPlay()
{
	AExplode::BeginPlay();
	this->SetActorScale3D(FVector(1.25f, 1.0f, 1.25f));
}
