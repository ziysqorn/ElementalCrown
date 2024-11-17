// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ConsumeAura.h"
#include "ManaAura.generated.h"

/**
 * 
 */

UCLASS()
class ELEMENTALCROWN_API AManaAura : public AConsumeAura
{
	GENERATED_BODY()
	
public:
	AManaAura();

	void BeginPlay() override;
};
