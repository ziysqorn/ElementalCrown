// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEffect.h"

// Sets default values
ASkillEffect::ASkillEffect()
{
}

ASkillEffect::ASkillEffect(const TCHAR* Ref)
{
	//Set projectile flipbook
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRef(Ref);
	Flipbook = FlipbookRef.Object;
	//Set up components
	if (!FlipbookComponent) {
		FlipbookComponent = this->CreateDefaultSubobject<UPaperFlipbookComponent>("Projectile");
		FlipbookComponent->SetupAttachment(RootComponent);
	}
	//Set flipbook component's flipbook
	if (Flipbook) {
		FlipbookComponent->SetLooping(true);
		FlipbookComponent->SetFlipbook(Flipbook);
	}
	FlipbookComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	FlipbookComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
}

ASkillEffect::~ASkillEffect()
{
	if (EffectElement) {
		delete EffectElement;
		EffectElement = nullptr;
	}
}

// Called when the game starts or when spawned
void ASkillEffect::BeginPlay()
{
	Super::BeginPlay();
	
}
