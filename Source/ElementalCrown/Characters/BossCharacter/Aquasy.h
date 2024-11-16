// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossCharacter.h"
#include "Aquasy.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AAquasy : public ABossCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SurfCurveFloat")
	UCurveFloat* SurfCurveFloat = nullptr;

	FTimeline SurfTimeline;

	FTimerHandle EndSurfTimer;

public:
	AAquasy();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnTimelinePostUpdate();

	void Surf();

	void MakeDecision() override;
};
