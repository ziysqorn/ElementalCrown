// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsPopout.h"

// Sets default values
AStatsPopout::AStatsPopout()
{
	PrimaryActorTick.bCanEverTick = true;
	StatsText = CreateDefaultSubobject<UWidgetComponent>("Stats text");
	StatsText->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStatsPopout::BeginPlay()
{
	Super::BeginPlay();
	
	if (CF_StatsPopout) {
		StatsPopoutTimeline.AddInterpFloat(CF_StatsPopout, FOnTimelineFloatStatic::CreateLambda([this](const float& Value) {
			if (this->GetOwner() && this->GetStatsPopoutUI()) {
				AActor* owner = this->GetOwner();
				UStatsPopoutUI* statsUI = this->GetStatsPopoutUI();
				FVector ActorLocation = owner->GetActorLocation();
				FVector newPosition = FVector(ActorLocation.X + 60.0f * Value, 0.0f, ActorLocation.Z + 60.0f * Value);
				this->SetActorLocation(newPosition);
				//statsUI->SetRenderOpacity(FMath::Lerp(1.0f, 0.0f, Value));
			}
			}));
	}
	StatsPopoutTimeline.PlayFromStart();
	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
	}), 1.0f, false);
}

void AStatsPopout::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	StatsPopoutTimeline.TickTimeline(DeltaSeconds);
}



