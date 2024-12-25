// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenMessage.h"
#include "TheEndMessage.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UTheEndMessage : public UScreenMessage
{
	GENERATED_BODY()

protected:
	void AnimEndAction() override;
};
