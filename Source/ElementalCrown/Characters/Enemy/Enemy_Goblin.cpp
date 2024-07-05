// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Goblin.h"

AEnemy_Goblin::AEnemy_Goblin()
{
	//Set character's base stats
	MaxHealth = Default_Character_MaxHealth - 50;
	CurrentHealth = MaxHealth;
	//Set character's element
	CharacterElement = new CustomNode<Elemental>(new Metal(this));
	//
	WallDetectBox = FVector(20, 0, 37);
}

