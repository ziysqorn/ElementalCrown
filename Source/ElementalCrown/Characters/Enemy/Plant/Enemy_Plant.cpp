#include "Enemy_Plant.h"

AEnemy_Plant::AEnemy_Plant()
{
}

void AEnemy_Plant::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UPlant>(this, TEXT("CharacterElement"));
}
