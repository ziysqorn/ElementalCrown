// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenMessage.h"
#include "CongratulationsMessage.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UCongratulationsMessage : public UScreenMessage
{
	GENERATED_BODY()

protected:
	void AnimEndAction() override;
};
