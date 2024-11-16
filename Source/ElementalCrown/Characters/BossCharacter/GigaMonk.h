// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossCharacter.h"
#include "GigaMonk.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AGigaMonk : public ABossCharacter
{
	GENERATED_BODY()

public:
	AGigaMonk();

	void BeginPlay() override;
};
