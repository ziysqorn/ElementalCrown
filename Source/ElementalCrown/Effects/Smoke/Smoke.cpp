// Fill out your copyright notice in the Description page of Project Settings.


#include "Smoke.h"

// Sets default values
ASmoke::ASmoke()
{
	//Setup components
	if (!FlipbookComponent) {
		FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook Component");
		FlipbookComponent->SetupAttachment(RootComponent);
	}
}

ASmoke::ASmoke(const TCHAR* Ref)
{
	//Set flipbook asset
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRef(Ref);
	SmokeFB = FlipbookRef.Object;
	//Setup components
	if (!FlipbookComponent) {
		FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook Component");
		FlipbookComponent->SetupAttachment(RootComponent);
	}
	if (SmokeFB) {
		FlipbookComponent->SetLooping(false);
		FlipbookComponent->SetFlipbook(SmokeFB);
	}
}

// Called when the game starts or when spawned
void ASmoke::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorScale3D(FVector(2, 1, 2));
	
	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
	}), SmokeFB->GetTotalDuration(), false);
}
