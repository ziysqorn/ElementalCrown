// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseEnemyCharacter.h"
#include "../../../Effects/Skills/SkillCC/FireWispExplode/FireWispExplode.h"
#include "Enemy_Fire.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API AEnemy_Fire : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	//************************************* CONSTRUCTOR *****************************************
	AEnemy_Fire();
	//************************************* EVENTS **********************************************************
	virtual void BeginPlay() override;
	//************************************* ACTIONS *********************************************************
	void TriggerExplosion();
	void Dead() override;
};
