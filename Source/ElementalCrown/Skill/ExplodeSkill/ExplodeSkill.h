// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseSkill.h"

/**
 * 
 */
class ELEMENTALCROWN_API ExplodeSkill : public BaseSkill
{
protected:
	FVector SpawnLocation;
	FRotator SpawnRotation;
	float SpawnDistanceX;
public:
	ExplodeSkill();
	ExplodeSkill(const TCHAR* Ref);
	virtual ~ExplodeSkill();
	void PerformSkill() override;
};
