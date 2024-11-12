#include "Enemy_Metal.h"

AEnemy_Metal::AEnemy_Metal()
{
}

void AEnemy_Metal::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UMetal>(this, TEXT("CharacterElement"));
}
