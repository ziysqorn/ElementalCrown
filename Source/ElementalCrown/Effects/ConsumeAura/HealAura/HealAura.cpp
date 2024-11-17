// Fill out your copyright notice in the Description page of Project Settings.


#include "HealAura.h"

AHealAura::AHealAura() : AConsumeAura(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/ConsumeAura/HealAura/Effect_HealAura.Effect_HealAura'"))
{

}

void AHealAura::BeginPlay()
{
	Super::BeginPlay();

	StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 2.0f, 9.0f));
	StatusFlipbookComp->SetRelativeScale3D(FVector(3.0f, 0.0f, 2.0f));
	MirroredFlipbookComp->SetRelativeLocation(FVector(0.0f, -2.0f, 9.0f));
	MirroredFlipbookComp->SetRelativeScale3D(FVector(3.0f, 0.0f, 2.0f));
}
