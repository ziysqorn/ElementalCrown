// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackAnimNotify.h"
#include "Attack3AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UAttack3AnimNotify : public UAttackAnimNotify
{
	GENERATED_BODY()
public:
	UAttack3AnimNotify();
	void SetBuff() override;
};
