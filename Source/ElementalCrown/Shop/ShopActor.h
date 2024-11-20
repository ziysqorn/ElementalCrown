// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Skill/BaseSkill.h"
#include "../Consumable/Consumable.h"
#include "ShopActor.generated.h"

UCLASS()
class ELEMENTALCROWN_API AShopActor : public AActor
{
	GENERATED_BODY()

protected:
	TArray<Consumable*> AvailableConsumables;

	TArray<BaseSkill*> AvailableSkills;

public:	
	// Sets default values for this actor's properties
	AShopActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
