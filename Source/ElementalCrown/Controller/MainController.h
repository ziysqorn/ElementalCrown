// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaperSprite.h"
#include "../UI/MainCharacterHUB.h"
#include "../GameplayElemental/Elemental.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AMainController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main HUB sub class")
	TSubclassOf<UMainCharacterHUB> MainHUBSubClass;

	UMainCharacterHUB* MainHUB = nullptr;
public:
	void BeginPlay() override;
	void SetupHUB();
};
