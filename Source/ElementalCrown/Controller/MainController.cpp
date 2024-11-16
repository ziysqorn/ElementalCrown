// Fill out your copyright notice in the Description page of Project Settings.


#include "MainController.h"

void AMainController::BeginPlay()
{
	Super::BeginPlay();
	if (MainHUDSubClass) {
		MainHUD = CreateWidget<UMainCharacterHUD>(this, MainHUDSubClass);
		if (MainHUD) {
			MainHUD->SetOwningPlayer(this);
			MainHUD->SetupHUD();
			MainHUD->AddToViewport(10);
		}
	}
}
