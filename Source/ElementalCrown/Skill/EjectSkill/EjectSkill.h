// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseSkill.h"

/**
 * 
 */
class ELEMENTALCROWN_API EjectSkill : public BaseSkill
{
protected:
	FVector SpawnLocation;
	FRotator SpawnRotation;
public:
	//*************** CONSTRUCTOR *************************
	EjectSkill();
	EjectSkill(const TCHAR* Ref);
	virtual ~EjectSkill();
};
