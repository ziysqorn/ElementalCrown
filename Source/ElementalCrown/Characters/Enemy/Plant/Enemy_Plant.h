// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseEnemyCharacter.h"
#include "Enemy_Plant.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API AEnemy_Plant : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	//************************************* CONSTRUCTOR *****************************************
	AEnemy_Plant();
	//************************************* EVENTS **********************************************************
	virtual void BeginPlay() override;
	//************************************* ACTIONS *********************************************************
};
