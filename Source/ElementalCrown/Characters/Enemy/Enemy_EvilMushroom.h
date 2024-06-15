// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Enemy/BaseEnemyCharacter.h"
#include "Enemy_EvilMushroom.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AEnemy_EvilMushroom : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	//************************************* CONSTRUCTOR *****************************************
	AEnemy_EvilMushroom();
	~AEnemy_EvilMushroom();
	//************************************* EVENTS **********************************************************
	void BeginPlay() override;
	//Event Tick
	void Tick(float DeltaSeconds) override;
	//************************************* ACTIONS *********************************************************
};
