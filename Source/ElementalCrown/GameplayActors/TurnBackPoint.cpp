// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBackPoint.h"
#include "../Characters/Enemy/BaseEnemyCharacter.h"

// Sets default values
ATurnBackPoint::ATurnBackPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootSceneComp->SetupAttachment(RootComponent);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootSceneComp);

	this->OnActorBeginOverlap.AddDynamic(this, &ATurnBackPoint::BeginOverlap);
}

// Called when the game starts or when spawned
void ATurnBackPoint::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
}

void ATurnBackPoint::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}
