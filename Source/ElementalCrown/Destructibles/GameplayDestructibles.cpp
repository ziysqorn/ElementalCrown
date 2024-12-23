// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayDestructibles.h"
#include "../Characters/Main Character/MainCharacter.h"



// Sets default values
AGameplayDestructibles::AGameplayDestructibles()
{
}

AGameplayDestructibles::AGameplayDestructibles(const TCHAR* SpriteRef, const TCHAR* DamagedSpriteRef, const TCHAR* CurveRef)
{
	this->PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UPaperSprite> IniSpriteRef(SpriteRef);
	ConstructorHelpers::FObjectFinder<UPaperSprite> DamagedRef(DamagedSpriteRef);
	ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloatRef(CurveRef);
	if (IniSpriteRef.Object) {
		IniSprite = IniSpriteRef.Object;
	}
	if (DamagedRef.Object) {
		DamagedSprite = DamagedRef.Object;
	}
	if (CurveFloatRef.Object) {
		FlashCurveFloat = CurveFloatRef.Object;
	}
	if (!ObjectSprite) {
		ObjectSprite = this->CreateDefaultSubobject<UPaperSpriteComponent>("Object Sprite");
		ObjectSprite->SetupAttachment(RootComponent);
	}
	if (IniSprite) {
		ObjectSprite->SetSprite(IniSprite);
	}
}

void AGameplayDestructibles::FlashDamage(const float &Value)
{
	UMaterialInstanceDynamic* DynamicMaterial = ObjectSprite->CreateDynamicMaterialInstance(0);
	DynamicMaterial->SetScalarParameterValue("FlashMultiplier", Value);
}

// Called when the game starts or when spawned
void AGameplayDestructibles::BeginPlay()
{
	Super::BeginPlay();
	if (FlashCurveFloat) {
		FlashTimeline.AddInterpFloat(FlashCurveFloat, FOnTimelineFloatStatic::CreateUFunction(this, "FlashDamage"));
	}
}

void AGameplayDestructibles::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FlashTimeline.TickTimeline(DeltaSeconds);
}

float AGameplayDestructibles::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Health Calculating
	if (Health > 0) {
		FlashTimeline.PlayFromStart();
		Health -= (int)DamageAmount;
	}
	if (Health <= 0) {
		DestructibleDestroyed();
	}
	return 0.0f;
}

void AGameplayDestructibles::DestructibleDestroyed()
{
	ObjectSprite->SetSprite(DamagedSprite);
	ObjectSprite->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		if (AMainCharacter* MainCharacter = PlayerController->GetPawn<AMainCharacter>()) {
			if (UGoldComponent* GoldComp = MainCharacter->GetGoldComp()) {
				int randomPrice = FMath::RandRange(5, maxBountyPrice);
				GoldComp->AddGold(randomPrice);
			}
		}
	}
	GetWorldTimerManager().SetTimer(DeadHandle, FTimerDelegate::CreateUObject(this, &AGameplayDestructibles::SelfDestroy), 1.0f, false);
}

void AGameplayDestructibles::SelfDestroy()
{
	this->Destroy();
}
