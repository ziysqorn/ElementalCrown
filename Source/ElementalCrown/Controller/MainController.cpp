// Fill out your copyright notice in the Description page of Project Settings.


#include "MainController.h"
#include "../Characters/Main Character/MainCharacter.h"

void AMainController::BeginPlay()
{
	Super::BeginPlay();
}

void AMainController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(inPawn)) {
		MainCharacter->SetupMappingContext();

		MainCharacter->LoadInfoFromSave();

		MainCharacter->LoadGameplayFromSave();


		if (MainHUDSubClass) {
			MainHUD = CreateWidget<UMainCharacterHUD>(this, MainHUDSubClass);
			if (MainHUD) {
				MainHUD->SetupHUD();
				MainHUD->SetOwningPlayer(this);
				MainHUD->AddToViewport(10);
			} 
		}

		if (PauseMenuUISubClass) {
			PauseMenuUI = CreateWidget<UPauseMenuUI>(this, PauseMenuUISubClass);
			if (PauseMenuUI) PauseMenuUI->SetOwningPlayer(this);
		}


		if (DeadMessageSubclass) {
			DeadMessage = CreateWidget<UDeadMessage>(this, DeadMessageSubclass);
			if (DeadMessage) DeadMessage->SetOwningPlayer(this);
		}

		if (BossDefeatMessageSubclass) {
			BossDefeatMessage = CreateWidget<UBossDefeatMessage>(this, BossDefeatMessageSubclass);
			if (BossDefeatMessage) BossDefeatMessage->SetOwningPlayer(this);
		}

		if (BossHealthBarSubclass) {
			BossHealthBar = CreateWidget<UBossHealthBar>(this, BossHealthBarSubclass);
			if (BossHealthBar) BossHealthBar->SetOwningPlayer(this);
		}
	}
}

void AMainController::PauseGame()
{
	if (PauseMenuUI) {
		PauseMenuUI->AddToViewport(12);
		PauseMenuUI->SetFocus();
		this->SetShowMouseCursor(true);
		if(this->GetPawn()) this->GetPawn()->DisableInput(this);
		UGameplayStatics::SetGlobalTimeDilation(this->GetWorld(), 0.0f);
	}
}

void AMainController::DeadMessageDisplay()
{
	if (DeadMessage) {
		DeadMessage->AddToViewport(11);
		DeadMessage->PlayFadein();
	}
}

void AMainController::BossDefeatMessageDisplay()
{
	if (BossDefeatMessage) {
		BossDefeatMessage->AddToViewport(11);
		BossDefeatMessage->PlayFadein();
	}
}

void AMainController::BossHealthBarDisplay()
{
	if (BossHealthBar) {
		BossHealthBar->AddToViewport(11);
	}
}
