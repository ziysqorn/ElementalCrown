// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossCharacter.h"
#include "Silvas.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API ASilvas : public ABossCharacter
{
	GENERATED_BODY()
	
public:
	ASilvas();

	void BeginPlay() override;
};
