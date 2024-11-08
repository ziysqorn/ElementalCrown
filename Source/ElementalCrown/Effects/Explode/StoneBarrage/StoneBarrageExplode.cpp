// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneBarrageExplode.h"

AStoneBarrageExplode::AStoneBarrageExplode() : AExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/StoneBarrageExplosion/Effect_Explosion_StoneBarrge.Effect_Explosion_StoneBarrge'"))
{

}

void AStoneBarrageExplode::BeginPlay()
{
	AExplode::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2));
}
