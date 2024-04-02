// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Explode.h"
#include "FireSlashWaveExplode.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AFireSlashWaveExplode : public AExplode
{
	GENERATED_BODY()
public:
	AFireSlashWaveExplode();
	//Event begin play
	void BeginPlay() override;
};
