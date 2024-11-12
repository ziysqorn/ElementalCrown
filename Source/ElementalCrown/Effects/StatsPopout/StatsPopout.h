// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../UI/StatsPopoutUI/StatsPopoutUI.h"
#include "StatsPopout.generated.h"

UCLASS()
class ELEMENTALCROWN_API AStatsPopout : public AActor
{
	GENERATED_BODY()

protected:
	float DistanceX = 60.0f;
	float DistanceZ = 60.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats Text")
	UWidgetComponent* StatsText = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "CurveFloats | StatsOpacity")
	UCurveFloat* CF_StatsPopout = nullptr;

	FTimerHandle DestroyHandle;
	FTimeline StatsPopoutTimeline;
	
public:	
	// Sets default values for this actor's properties
	AStatsPopout();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UStatsPopoutUI* GetStatsPopoutUI() {
		if (UStatsPopoutUI* statsUI = Cast<UStatsPopoutUI>(StatsText->GetWidget())) return statsUI;
		return nullptr;
	}

	void setDistanceX(const float& newDistance) {
		DistanceX = newDistance;
	}
	
	void setDistanceZ(const float& newDistance) {
		DistanceZ = newDistance;
	}
};
