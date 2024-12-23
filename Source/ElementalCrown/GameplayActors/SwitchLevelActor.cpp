// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchLevelActor.h"
#include "../CustomGameInstance/CustomGameInstance.h"

// Sets default values
ASwitchLevelActor::ASwitchLevelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("RootSceneComponent");
	SwitchLevelBox = CreateDefaultSubobject<UBoxComponent>("SwitchLevelBoxComp");

	SceneComponent->SetupAttachment(RootComponent);
	SwitchLevelBox->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	OnActorBeginOverlap.AddDynamic(this, &ASwitchLevelActor::BeginOverlap);
}

// Called when the game starts or when spawned
void ASwitchLevelActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASwitchLevelActor::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
		MainCharacter->SaveGameplay();
		MainCharacter->SavePlayerInfo();
		MainCharacter->SaveGameProgress(NextLevelName, FVector(0.0f, 0.0f, 0.0f));
		if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
			CustomGameInstance->SpawnLoadingScreen();
			CustomGameInstance->OpenLevel(NextLevelName);
		}
	}
}

