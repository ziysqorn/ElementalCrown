// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"

UConsumable::UConsumable()
{
}

UConsumable::UConsumable(const TCHAR* Ref)
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite(Ref);
	if (Sprite.Succeeded()) Avatar = Sprite.Object;
}
