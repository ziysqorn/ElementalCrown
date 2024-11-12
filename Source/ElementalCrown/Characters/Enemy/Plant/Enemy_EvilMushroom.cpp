// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_EvilMushroom.h"

AEnemy_EvilMushroom::AEnemy_EvilMushroom()
{
	//Set character's base stats
	MaxHealth = Default_Character_MaxHealth - 50;
	CurrentHealth = MaxHealth;
}


