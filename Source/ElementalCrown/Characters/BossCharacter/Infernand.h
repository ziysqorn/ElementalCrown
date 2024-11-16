// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossCharacter.h"
#include "Infernand.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AInfernand : public ABossCharacter
{
	GENERATED_BODY()
	
public:
	AInfernand();

	void BeginPlay() override;
};
