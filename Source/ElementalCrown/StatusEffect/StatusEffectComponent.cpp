// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"


UStatusEffectComponent::UStatusEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UStatusEffectComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

