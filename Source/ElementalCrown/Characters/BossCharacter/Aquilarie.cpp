// Fill out your copyright notice in the Description page of Project Settings.


#include "Aquilarie.h"

AAquilarie::AAquilarie()
{
	CharacterName = FName("Aquilarie");
	NextLevelName = FName("Rocky");
}

void AAquilarie::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UPlant>(this, TEXT("CharacterElement"));
}
