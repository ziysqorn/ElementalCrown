// Fill out your copyright notice in the Description page of Project Settings.


#include "Aquilarie.h"

AAquilarie::AAquilarie()
{
	CharacterName = FName("Aquilarie");
}

void AAquilarie::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UPlant>(this, TEXT("CharacterElement"));
}
