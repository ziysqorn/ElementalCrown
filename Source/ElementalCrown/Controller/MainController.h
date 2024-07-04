// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UI/MainCharacterHUD.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AMainController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main HUD sub class")
	TSubclassOf<UMainCharacterHUD> MainHUDSubClass;

	UMainCharacterHUD* MainHUD = nullptr;
public:
	void BeginPlay() override;
	UMainCharacterHUD* GetMainHUD() { return MainHUD; }
};
