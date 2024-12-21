// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UI/MainCharacterHUD.h"
#include "../UI/PauseMenu/PauseMenuUI.h"
#include "../UI/ScreenMessage/DeadMessage.h"
#include "../UI/ScreenMessage/BossDefeatMessage.h"
#include "../UI/BossHealthBar/BossHealthBar.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AMainController : public APlayerController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void OnPossess(APawn* inPawn) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main HUD sub class")
	TSubclassOf<UMainCharacterHUD> MainHUDSubClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pause Menu sub class")
	TSubclassOf<UPauseMenuUI> PauseMenuUISubClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dead Message sub class")
	TSubclassOf<UDeadMessage> DeadMessageSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss Defeat Message sub class")
	TSubclassOf<UBossDefeatMessage> BossDefeatMessageSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss Healthbar sub class")
	TSubclassOf<UBossHealthBar> BossHealthBarSubclass;

	UPROPERTY()
	UMainCharacterHUD* MainHUD = nullptr;

	UPROPERTY()
	UPauseMenuUI* PauseMenuUI = nullptr;

	UPROPERTY()
	UDeadMessage* DeadMessage = nullptr;

	UPROPERTY()
	UBossDefeatMessage* BossDefeatMessage = nullptr;

	UPROPERTY()
	UBossHealthBar* BossHealthBar = nullptr;


public:
	UMainCharacterHUD* GetMainHUD() { return MainHUD; }
	UPauseMenuUI* GetPauseMenuUI() { return PauseMenuUI; }
	UBossDefeatMessage* GetBossDefeatMessage() { return BossDefeatMessage; }
	UBossHealthBar* GetBossHealthBar() { return BossHealthBar; }

	UFUNCTION()
	void PauseGame();

	void DeadMessageDisplay();

	void BossDefeatMessageDisplay();

	void BossHealthBarDisplay();
};
