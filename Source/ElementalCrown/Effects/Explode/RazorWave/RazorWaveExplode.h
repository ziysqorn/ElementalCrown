// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Explode.h"
#include "RazorWaveExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ARazorWaveExplode : public AExplode
{
	GENERATED_BODY()
public:
	ARazorWaveExplode();
	void BeginPlay() override;
};
