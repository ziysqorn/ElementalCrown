// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatusEffect.h"

BaseStatusEffect::BaseStatusEffect()
{

}

BaseStatusEffect::BaseStatusEffect(const TCHAR* AvtRef, const TCHAR* FlipbookRef)
{
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, AvtRef));
	UPaperFlipbook* Flipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, FlipbookRef));
	if (Sprite && Flipbook) {
		StatusAvt = Sprite;
		StatusFlipbook = Flipbook;
	}
}

BaseStatusEffect::~BaseStatusEffect()
{
	StatusFlipbookComp->DestroyComponent();
	StatusFlipbookComp = nullptr;
}

void BaseStatusEffect::SetAvtFromRef(const TCHAR* AvtRef)
{
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, AvtRef));
	if (Sprite) StatusAvt = Sprite;
}

