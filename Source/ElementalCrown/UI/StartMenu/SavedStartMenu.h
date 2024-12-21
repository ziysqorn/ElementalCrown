// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../CustomSave/GameProgress.h"
#include "../../UI/LoadingScreen/LoadingScreen.h"
#include "SavedStartMenu.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API USavedStartMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_Continue = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_NewGame = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_QuitGame = nullptr;

	FTimerHandle SwitchLevelHandle;

	UFUNCTION()
	void ContinueGame();

	UFUNCTION()
	void StartNewGame();

	UFUNCTION()
	void QuitGame();
};
