// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Explode.h"
#include "LumberLaunchExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ALumberLaunchExplode : public AExplode
{
	GENERATED_BODY()
public:
	ALumberLaunchExplode();
	void BeginPlay() override;
};
