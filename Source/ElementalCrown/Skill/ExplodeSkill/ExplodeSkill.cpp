// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodeSkill.h"

ExplodeSkill::ExplodeSkill()
{
	CooldownTime = 7.00f;
	SpawnDistanceX = 50.00f;
	ManaConsumption = 5;
}

ExplodeSkill::ExplodeSkill(const TCHAR* Ref) : BaseSkill(Ref)
{
	CooldownTime = 7.00f;
	SpawnDistanceX = 50.00f;
}

ExplodeSkill::~ExplodeSkill()
{
}

