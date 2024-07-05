// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_SwordSkeleton.h"

AEnemy_SwordSkeleton::AEnemy_SwordSkeleton()
{
	//Set character's base stats
	MaxHealth = Default_Character_MaxHealth - 50;
	CurrentHealth = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = 110.0f;
	//Set character's element
	CharacterElement = new CustomNode<Elemental>(new Metal(this));
	//
	PlayerDetectBox = FVector(150, 0, 40);
	WallDetectBox = FVector(20, 0, 40);
}
