// Fill out your copyright notice in the Description page of Project Settings.


#include "GigaMonk.h"

AGigaMonk::AGigaMonk()
{
	CharacterName = FName("Giga Monk");
}

void AGigaMonk::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UEarth>(this, TEXT("CharacterElement"));
}
