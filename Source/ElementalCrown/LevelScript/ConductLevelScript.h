// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../UI/DialogueUI/DialogueUI.h"
#include "../UI/LoadingScreen/LoadingScreen.h"
#include "../UI/ScreenMessage/ScreenMessage.h"
#include "ConductLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AConductLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Important | Dialogue UI subclass")
	TSubclassOf<UDialogueUI> DialogUISubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Background")
	TSubclassOf<ULoadingScreen>  BackgroundSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Message")
	TSubclassOf<UScreenMessage> ScreenMessageSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Next Level Name")
	FName NextLevelName;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Brush object")
	UObject* BrushObject = nullptr;

	UPROPERTY()
	UDialogueUI* DialogueUI = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Background theme")
	USoundBase* BackgroundTheme = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Conduct lines")
	TArray<FDialogueLine> DialogueLines;


	void BeginPlay() override;

	void ConductDoneAction();
};
