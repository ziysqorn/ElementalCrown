// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelScript.h"

void AStartLevelScript::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		if (UGameplayStatics::DoesSaveGameExist("GameProgress", 0)) {
			if (SavedStartMenuSubclass) {
				if (USavedStartMenu* SavedStartMenu = CreateWidget<USavedStartMenu>(PlayerController, SavedStartMenuSubclass)) {
					SavedStartMenu->AddToViewport();
					SavedStartMenu->SetFocus();
					PlayerController->SetShowMouseCursor(true);
				}
			}
		}
		else {
			if (StartMenuSubclass) {
				if (UStartMenuUI* StartMenu = CreateWidget<UStartMenuUI>(PlayerController, StartMenuSubclass)) {
					StartMenu->AddToViewport();
					StartMenu->SetFocus();
					PlayerController->SetShowMouseCursor(true);
				}
			}
		}
		if (BackgroundTheme) {
			UGameplayStatics::PlaySound2D(this, BackgroundTheme);
		}
	}
}
