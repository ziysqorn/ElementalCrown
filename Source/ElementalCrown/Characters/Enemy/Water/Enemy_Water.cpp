#include "Enemy_Water.h"

AEnemy_Water::AEnemy_Water()
{
}

void AEnemy_Water::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UWater>(this, TEXT("CharacterElement"));
}
