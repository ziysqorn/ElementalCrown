// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../CustomSave/GameProgress.h"
#include "../../UI/LoadingScreen/LoadingScreen.h"
#include "StartMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UStartMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* Btn_NewGame = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* Btn_QuitGame = nullptr;

	FTimerHandle SwitchLevelHandle;

	UFUNCTION()
	void StartNewGame();

	UFUNCTION()
	void QuitGame();
};
