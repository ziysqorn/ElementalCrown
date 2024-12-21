// Fill out your copyright notice in the Description page of Project Settings.


#include "Infernand.h"

AInfernand::AInfernand()
{
	CharacterName = FName("Infernand");
	NextLevelName = FName("TestFactory1");
}

void AInfernand::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UFire>(this, TEXT("CharacterElement"));
}
