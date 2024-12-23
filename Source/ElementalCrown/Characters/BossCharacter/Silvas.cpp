// Fill out your copyright notice in the Description page of Project Settings.


#include "Silvas.h"

ASilvas::ASilvas()
{
	CharacterName = FName("Silvas");
	NextLevelName = FName("Ending");
}

void ASilvas::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UMetal>(this, TEXT("CharacterElement"));
}
