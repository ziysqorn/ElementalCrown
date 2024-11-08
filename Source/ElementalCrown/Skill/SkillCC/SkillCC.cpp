// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillCC.h"

SkillCC::SkillCC()
{
	CooldownTime = 7.00f;
	ManaConsumption = 5;
}

SkillCC::SkillCC(const TCHAR* Ref) : BaseSkill(Ref)
{
	CooldownTime = 7.00f;
	ManaConsumption = 5;
}

SkillCC::~SkillCC()
{
}

