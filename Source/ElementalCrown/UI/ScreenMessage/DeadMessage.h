// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenMessage.h"
#include "DeadMessage.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UDeadMessage : public UScreenMessage
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;
	
	void NativeConstruct() override;

	FTimerHandle ReloadLevelHandle;

public:
	void AnimEndAction() override;

};
