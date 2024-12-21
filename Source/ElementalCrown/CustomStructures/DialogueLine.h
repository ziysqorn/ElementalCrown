// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "DialogueLine.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct ELEMENTALCROWN_API FDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "SpeakerName")
	FName SpeakerName;

	UPROPERTY(EditAnywhere, Category = "DialogueText")
	FText DialogueText;


};
