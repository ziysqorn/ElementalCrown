// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseEnemyCharacter.h"
#include "Enemy_Earth.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API AEnemy_Earth : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	//************************************* CONSTRUCTOR *****************************************
	AEnemy_Earth();
	//************************************* EVENTS **********************************************************
	virtual void BeginPlay() override;
	//************************************* ACTIONS *********************************************************
};
