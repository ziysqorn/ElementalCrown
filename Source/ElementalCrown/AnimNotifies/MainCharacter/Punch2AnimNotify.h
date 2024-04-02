// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Punch1AnimNotify.h"
#include "Punch2AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UPunch2AnimNotify : public UPunch1AnimNotify
{
	GENERATED_BODY()

public:
	void SetBuff() override;
	
};
