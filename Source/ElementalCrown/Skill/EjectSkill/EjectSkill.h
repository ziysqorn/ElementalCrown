// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseSkill.h"
#include "EjectSkill.generated.h"

/**
 * 
 */

UCLASS()
class ELEMENTALCROWN_API UEjectSkill : public UBaseSkill
{
	GENERATED_BODY()

protected:
	FVector SpawnLocation;
	FRotator SpawnRotation;
public:
	//*************** CONSTRUCTOR *************************
	UEjectSkill();
	UEjectSkill(const TCHAR* Ref);
};
