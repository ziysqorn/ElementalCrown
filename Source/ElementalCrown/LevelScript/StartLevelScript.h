// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../UI/StartMenu/StartMenuUI.h"
#include "../UI/StartMenu/SavedStartMenu.h"
#include "StartLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AStartLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Important | Start menu subclass")
	TSubclassOf<UStartMenuUI> StartMenuSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Saved start menu subclass")
	TSubclassOf<USavedStartMenu> SavedStartMenuSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Background theme")
	USoundBase* BackgroundTheme = nullptr;

	void BeginPlay() override;

};
