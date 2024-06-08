// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Explode.h"
#include "AquaSphereExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AAquaSphereExplode : public AExplode
{
	GENERATED_BODY()
	
public:
	AAquaSphereExplode();
	void BeginPlay() override;
};
