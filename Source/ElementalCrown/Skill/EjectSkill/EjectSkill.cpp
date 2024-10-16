// Fill out your copyright notice in the Description page of Project Settings.


#include "EjectSkill.h"

EjectSkill::EjectSkill()
{
	this->CooldownTime = 4.00f;
}

EjectSkill::EjectSkill(const TCHAR* Ref) : BaseSkill(Ref)
{
	this->CooldownTime = 4.00f;
}

EjectSkill::~EjectSkill()
{
}
