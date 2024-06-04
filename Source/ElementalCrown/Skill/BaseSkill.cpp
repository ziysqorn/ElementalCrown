// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkill.h"

// Sets default values
BaseSkill::BaseSkill()
{
}

BaseSkill::BaseSkill(const TCHAR* Ref)
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteRef(Ref);
	SkillSprite = SpriteRef.Object;
}

BaseSkill::~BaseSkill()
{
	if (SkillElement) {
		delete SkillElement;
		SkillElement = nullptr;
	}
}


