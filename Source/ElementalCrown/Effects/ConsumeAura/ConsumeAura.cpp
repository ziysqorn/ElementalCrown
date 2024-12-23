// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumeAura.h"

// Sets default values
AConsumeAura::AConsumeAura()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

AConsumeAura::AConsumeAura(const TCHAR* FlipbookRef)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UPaperFlipbook> Flipbook(FlipbookRef);
	if (Flipbook.Succeeded()) {
		RootComponent = CreateDefaultSubobject<USceneComponent>("Symmetric Point");
		MirroredFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Mirrored Flipbook Component");
		StatusFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook Component");
		MirroredFlipbookComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		StatusFlipbookComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		UPaperFlipbook* PaperFlipbook = Flipbook.Object;
		StatusFlipbookComp->SetFlipbook(PaperFlipbook);
		MirroredFlipbookComp->SetFlipbook(StatusFlipbookComp->GetFlipbook());
		if (MirroredFlipbookComp) MirroredFlipbookComp->SetLooping(false);
		if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(false);
	}
}

// Called when the game starts or when spawned
void AConsumeAura::BeginPlay()
{
	Super::BeginPlay();
	
	if (StatusFlipbookComp && StatusFlipbookComp->GetFlipbook()) {
		GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateUObject(this, &AConsumeAura::SelfDestroy), StatusFlipbookComp->GetFlipbookLength(), false);
	}

	StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 2.0f, 20.0f));
	StatusFlipbookComp->SetRelativeScale3D(FVector(3.0f, 1.0f, 1.5f));
	MirroredFlipbookComp->SetRelativeLocation(FVector(0.0f, -2.0f, 20.0f));
	MirroredFlipbookComp->SetRelativeScale3D(FVector(3.0f, 1.0f, 1.5f));
}

void AConsumeAura::SelfDestroy()
{
	this->Destroy();
}

