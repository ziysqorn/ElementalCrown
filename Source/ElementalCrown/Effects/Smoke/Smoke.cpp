// Fill out your copyright notice in the Description page of Project Settings.


#include "Smoke.h"

// Sets default values
ASmoke::ASmoke()
{
	//Setup components
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>("Default Root Component");
	DefaultRootComponent->SetupAttachment(RootComponent);
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook Component");
	FlipbookComponent->AttachToComponent(DefaultRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FlipbookComponent->SetLooping(false);
}

// Called when the game starts or when spawned
void ASmoke::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
	}), FlipbookComponent->GetFlipbook()->GetTotalDuration(), false);
}
