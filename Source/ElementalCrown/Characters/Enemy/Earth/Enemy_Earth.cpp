#include "Enemy_Earth.h"

AEnemy_Earth::AEnemy_Earth()
{
}

void AEnemy_Earth::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UEarth>(this, TEXT("CharacterElement"));
}
