#include "Enemy_Fire.h"
#include "../../Main Character/MainCharacter.h"

AEnemy_Fire::AEnemy_Fire()
{
}

void AEnemy_Fire::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UFire>(this, TEXT("CharacterElement"));
}

void AEnemy_Fire::TriggerExplosion()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AFireWispExplode>(AFireWispExplode::StaticClass(), this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
}

void AEnemy_Fire::Dead()
{
	StatusEffectComponent->ClearAllStatusEffect();
	CurrentState = CharacterState::DEATH;
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		if (AMainCharacter* MainCharacter = PlayerController->GetPawn<AMainCharacter>()) {
			if (UGoldComponent* GoldComponent = MainCharacter->GetGoldComp()) {
				int randomPrice = FMath::RandRange(6, maxBountyPrice);
				GoldComponent->AddGold(randomPrice);
			}
		}
	}
	TriggerExplosion();
	this->Destroy();
}