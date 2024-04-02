// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackAnimNotify.h"
#include "Attack2AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UAttack2AnimNotify : public UAttackAnimNotify
{
	GENERATED_BODY()
	
public:
	void SetBuff() override;
};
