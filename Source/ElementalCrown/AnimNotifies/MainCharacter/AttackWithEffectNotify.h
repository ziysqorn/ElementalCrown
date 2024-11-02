// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackAnimNotify.h"
#include "AttackWithEffectNotify.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API UAttackWithEffectNotify : public UAttackAnimNotify
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildupAmount")
	float BuildupAmount = 0.0f;
public:
	UAttackWithEffectNotify();
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};