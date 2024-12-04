// Fill out your copyright notice in the Description page of Project Settings.


#include "EjectSkill.h"

UEjectSkill::UEjectSkill()
{
	this->CooldownTime = 4.00f;
}

UEjectSkill::UEjectSkill(const TCHAR* Ref) : UBaseSkill(Ref)
{
	this->CooldownTime = 4.00f;
}

