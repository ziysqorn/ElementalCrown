// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackImpact.h"

// Sets default values
AAttackImpact::AAttackImpact()
{
}

AAttackImpact::AAttackImpact(const TCHAR* Ref)
{
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRef(Ref);
	if (FlipbookRef.Object) {
		ImpactFB = FlipbookRef.Object;
	}
	//Set up components
	if (!AttackImpact) {
		AttackImpact = CreateDefaultSubobject<UPaperFlipbookComponent>("Attack Impact");
		AttackImpact->SetupAttachment(RootComponent);
	}
	if (ImpactFB) {
		AttackImpact->SetLooping(false);
		AttackImpact->SetFlipbook(ImpactFB);
	}
}

// Called when the game starts or when spawned
void AAttackImpact::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorScale3D(FVector(2, 1, 2));

	if (AttackImpact) {
		GetWorldTimerManager().SetTimer(ImpactHandle, FTimerDelegate::CreateUObject(this, &AAttackImpact::SelfDestroy), AttackImpact->GetFlipbookLength(), false);
	}
}

void AAttackImpact::SelfDestroy()
{
	this->Destroy();
}

