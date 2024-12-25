// Fill out your copyright notice in the Description page of Project Settings.


#include "Silvas.h"
#include "../../Controller/MainController.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

ASilvas::ASilvas()
{
	CharacterName = FName("Silvas");
	NextLevelName = FName("Congratulations");
}

void ASilvas::BeginPlay()
{
	Super::BeginPlay();

	CharacterElement = NewObject<UMetal>(this, TEXT("CharacterElement"));
}
