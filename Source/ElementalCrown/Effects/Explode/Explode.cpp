// Fill out your copyright notice in the Description page of Project Settings.


#include "Explode.h"

// Sets default value
AExplode::AExplode()
{
}

AExplode::AExplode(const TCHAR* Ref)
{
	//Set Explode Flipbook Asset
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRef(Ref);
	if (FlipbookRef.Object) {
		ExplodeFB = FlipbookRef.Object;
	}
	//Set up components
	if (!ExplodeFBComp) {
		ExplodeFBComp = this->CreateDefaultSubobject<UPaperFlipbookComponent>("Explode");
		ExplodeFBComp->SetupAttachment(RootComponent);
	}
	//Set ExplodeFBComp's Flipbook
	if (ExplodeFB) {
		ExplodeFBComp->SetLooping(false);
		ExplodeFBComp->SetFlipbook(ExplodeFB);
	}
}

// Called when the game starts or when spawned
void AExplode::BeginPlay()
{
	Super::BeginPlay();

	//Timing actor destroy
	if (ExplodeFB)
		GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
		}), ExplodeFB->GetTotalDuration(), false);
}
