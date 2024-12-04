// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillCC.h"

USkillCC::USkillCC()
{
	CooldownTime = 7.00f;
	ManaConsumption = 5;
}

USkillCC::USkillCC(const TCHAR* Ref) : UBaseSkill(Ref)
{
	CooldownTime = 7.00f;
	ManaConsumption = 5;
}

