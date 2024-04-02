// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEnergyExplode.h"

AFireEnergyExplode::AFireEnergyExplode() : AExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/FireEnergyExplode/Effect_Skill_FireEnergyExplode.Effect_Skill_FireEnergyExplode'"))
{
}

void AFireEnergyExplode::BeginPlay()
{
	AExplode::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2));
}
