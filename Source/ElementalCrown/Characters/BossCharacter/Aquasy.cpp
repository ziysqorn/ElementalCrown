// Fill out your copyright notice in the Description page of Project Settings.


#include "Aquasy.h"

AAquasy::AAquasy()
{
	CharacterName = FName("Aquasy");
	NextLevelName = FName("Volcano1");
}

void AAquasy::BeginPlay()
{

	Super::BeginPlay();

	CharacterElement = NewObject<UWater>(this, TEXT("CharacterElement"));

	SurfTimeline.SetTimelineFinishedFunc(FOnTimelineEventStatic::CreateLambda([this]() {
		if (CurrentState == CharacterState::SURF) CurrentState = CharacterState::NONE;
		FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);
		this->SetActorRotation(this->GetActorRotation() + NewRotation);
		GetWorldTimerManager().SetTimer(NewDecisionTimer, FTimerDelegate::CreateUObject(this, &AAquasy::SetCanMakeDecision, true), NewDecisionTimeAmount, false);
	}));

	FOnTimelineEvent PostUpdateCallback;
	PostUpdateCallback.BindUFunction(this, FName("OnTimelinePostUpdate"));

	SurfTimeline.SetTimelinePostUpdateFunc(PostUpdateCallback);
}

void AAquasy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SurfTimeline.TickTimeline(DeltaSeconds);

	if (canMakeDecision) {
		MakeDecision();
	}
}

void AAquasy::OnTimelinePostUpdate()
{
	if (!hasDealtDmgToPlayer) {
		TArray<AActor*> actors;
		this->GetOverlappingActors(actors, AMainCharacter::StaticClass());
		for (int i = 0; i < actors.Num(); ++i) {
			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyDamage(actors[i], 7.0f, this->GetController(), this, DamageType);
			hasDealtDmgToPlayer = true;
		}
	}
}

void AAquasy::Surf()
{
	hasDealtDmgToPlayer = false;
	CurrentState = CharacterState::SURF;
	int ForwardDir = this->GetActorRotation().Yaw == 0.0f ? 1 : -1;
	FVector CurrentLoc = this->GetActorLocation();
	FVector Destination = CurrentLoc + FVector(550.0f * ForwardDir, 0.0f, 0.0f);
	if (SurfCurveFloat) {
		SurfTimeline.AddInterpFloat(SurfCurveFloat, FOnTimelineFloatStatic::CreateLambda([this, CurrentLoc, Destination](const float& Value) {
			FVector NewLocation = FMath::Lerp(CurrentLoc, Destination, Value);
			this->SetActorLocation(NewLocation, true);
		}));
		SurfTimeline.SetLooping(false);
		SurfTimeline.PlayFromStart();
	}
}

void AAquasy::MakeDecision()
{
	if (CurrentState == CharacterState::NONE) {
		int finalDecision = FMath::RandRange(1, 2);
		switch (finalDecision) {
		case 1:
			canMakeDecision = false;
			Attack();
			break;
		case 2:
			canMakeDecision = false;
			Surf();
			break;
		}
	}
}
