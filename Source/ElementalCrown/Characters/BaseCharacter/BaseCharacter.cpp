// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*if (FlashCurveFloat) {
		FlashTimeline.AddInterpFloat(FlashCurveFloat, FOnTimelineFloatStatic::CreateLambda([this](const float& Value) {
			UMaterialInstanceDynamic* DynamicMaterial = this->GetSprite()->CreateDynamicMaterialInstance(0);
			DynamicMaterial->SetScalarParameterValue("FlashMultiplier", Value);
		}));
	}*/
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FlashTimeline.TickTimeline(DeltaSeconds);
}
