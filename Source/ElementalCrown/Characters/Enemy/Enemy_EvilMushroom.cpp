// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_EvilMushroom.h"

AEnemy_EvilMushroom::AEnemy_EvilMushroom()
{
	//Set character's base stats
	MaxHealth = Default_Character_MaxHealth - 50;
	CurrentHealth = MaxHealth;
	//Set character's element
	ElementalType = new Plant();
}

AEnemy_EvilMushroom::~AEnemy_EvilMushroom()
{
	if (ElementalType) {
		delete ElementalType;
		ElementalType = nullptr;
	}
}

void AEnemy_EvilMushroom::BeginPlay()
{
	ABaseEnemyCharacter::BeginPlay();
	if (UUserWidget* widget = EnemyHealthBar->GetUserWidgetObject()) {
		if (UEnemyHealthBar* healthBar = Cast<UEnemyHealthBar>(widget)) {
			healthBar->SetDelegateForHealthBar(this, FName("GetHealthPercentage"));
		}
	}
}

void AEnemy_EvilMushroom::Tick(float DeltaSeconds)
{
	ABaseEnemyCharacter::Tick(DeltaSeconds);
	if (DetectingPlayer()) {
		this->Attack();
	}
}

