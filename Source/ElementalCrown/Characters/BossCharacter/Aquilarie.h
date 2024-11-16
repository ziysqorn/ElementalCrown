// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossCharacter.h"
#include "Aquilarie.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AAquilarie : public ABossCharacter
{
	GENERATED_BODY()

public:
	AAquilarie();

	void BeginPlay() override;
};
