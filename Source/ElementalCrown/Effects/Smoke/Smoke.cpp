// Fill out your copyright notice in the Description page of Project Settings.


#include "Smoke.h"

// Sets default values
ASmoke::ASmoke()
{
	//Setup components
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>("Default Root Component");
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook Component");
	RootComponent = DefaultRootComponent;
	FlipbookComponent->AttachToComponent(DefaultRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FlipbookComponent->SetLooping(false);
}

// Called when the game starts or when spawned
void ASmoke::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateUObject(this, &ASmoke::SelfDestroy), FlipbookComponent->GetFlipbook()->GetTotalDuration(), false);
}

void ASmoke::SelfDestroy()
{
	this->Destroy();
}
