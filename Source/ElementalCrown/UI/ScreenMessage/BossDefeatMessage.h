// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenMessage.h"
#include "BossDefeatMessage.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UBossDefeatMessage : public UScreenMessage
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;

	void NativeConstruct() override;

public:
	FName BossName;

	FName NextLevelName;

	void AnimEndAction() override;
};
