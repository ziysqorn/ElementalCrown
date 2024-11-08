// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Explode.h"
#include "StoneBarrageExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AStoneBarrageExplode : public AExplode
{
	GENERATED_BODY()
public:
	AStoneBarrageExplode();
	void BeginPlay() override;
};
