// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTALCROWN_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

protected:


public:	
	UStatusEffectComponent();

protected:
	virtual void BeginPlay() override;
		
};
