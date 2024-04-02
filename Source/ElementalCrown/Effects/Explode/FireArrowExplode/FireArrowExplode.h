// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Explode.h"
#include "FireArrowExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AFireArrowExplode : public AExplode
{
	GENERATED_BODY()
public:
	AFireArrowExplode();
	void BeginPlay() override;
};
