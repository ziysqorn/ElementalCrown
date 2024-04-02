// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Punch1AnimNotify.h"
#include "Kick1AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UKick1AnimNotify : public UPunch1AnimNotify
{
	GENERATED_BODY()

public:
	void SetBuff() override;
};
