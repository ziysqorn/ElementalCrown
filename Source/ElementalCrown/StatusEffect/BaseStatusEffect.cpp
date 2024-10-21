// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatusEffect.h"

BaseStatusEffect::BaseStatusEffect()
{

}

BaseStatusEffect::BaseStatusEffect(const TCHAR* AvtRef)
{
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, AvtRef));
	if (Sprite) StatusAvt = Sprite;
}
