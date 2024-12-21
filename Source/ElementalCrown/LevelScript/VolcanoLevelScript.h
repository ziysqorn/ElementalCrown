// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../CustomSave/GameProgress.h"
#include "../UI/LoadingScreen/LoadingScreen.h"
#include "VolcanoLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AVolcanoLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Important | Main Character subclass")
	TSubclassOf<AMainCharacter> MainCharSubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Level Tilemap")
	UPaperTileMap* LevelTilemap = nullptr;

	void BeginPlay() override;
};
