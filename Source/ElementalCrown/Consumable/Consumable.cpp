// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"

Consumable::Consumable()
{
}

Consumable::Consumable(const TCHAR* Ref)
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite(Ref);
	if (Sprite.Succeeded()) Avatar = Sprite.Object;
}

Consumable::~Consumable()
{
}
