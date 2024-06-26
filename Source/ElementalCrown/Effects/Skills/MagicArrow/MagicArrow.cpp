// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicArrow.h"

// Sets default values
AMagicArrow::AMagicArrow()
{
}

AMagicArrow::AMagicArrow(const TCHAR* Ref)
{
	//Set Explode Flipbook Asset
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRef(Ref);
	ArrowFB = FlipbookRef.Object;
	//Set up components
	if (!ArrowComponent) {
		ArrowComponent = this->CreateDefaultSubobject<UPaperFlipbookComponent>("Arrow FlipBook");
		ArrowComponent->SetupAttachment(RootComponent);
	}
	if (!ProjectileMovement) {
		ProjectileMovement = this->CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
		//Initial projectile movement settings
		ProjectileMovement->InitialSpeed = 1000;
		ProjectileMovement->MaxSpeed = 1000;
		ProjectileMovement->ProjectileGravityScale = 0;
	}
	//Set ExplodeFBComp's Flipbook
	if (ArrowFB) {
		ArrowComponent->SetLooping(false);
		ArrowComponent->SetFlipbook(ArrowFB);
	}
	this->OnActorBeginOverlap.AddDynamic(this, &AMagicArrow::BeginOverlap);
}

// Called when the game starts or when spawned
void AMagicArrow::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExpiredHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
	}), 4, false);
}

void AMagicArrow::SetBuff()
{
	Buff = -2;
}

void AMagicArrow::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AFireArrowExplode>(AFireArrowExplode::StaticClass(), this->GetActorLocation(), this->GetActorRotation(), SpawnParams);
	this->Destroy();
}

void AMagicArrow::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (this->GetOwner()) {
		if (OtherActor != this->GetOwner()) {
			if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
				TSubclassOf<UDamageType> DamageType;
				AMagicArrow::SetBuff();
				UGameplayStatics::ApplyDamage(OtherActor, OwningCharacter->CalculatedDamage(Buff), OwningCharacter->GetController(), OwningCharacter, DamageType);
			}
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			GetWorld()->SpawnActor<AFireArrowExplode>(AFireArrowExplode::StaticClass(), this->GetActorLocation(), this->GetActorRotation(), SpawnParams);
			this->Destroy();
		}
	}
}

