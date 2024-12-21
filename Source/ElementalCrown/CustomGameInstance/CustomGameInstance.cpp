// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "../Controller/MainController.h"
#include "../Characters/Main Character/MainCharacter.h"

void UCustomGameInstance::SpawnLoadingScreen()
{
	if (LoadingScreenSubclass) {
		if (!LoadingScreen) {
			LoadingScreen = CreateWidget<ULoadingScreen>(this, LoadingScreenSubclass);
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnim();
		}
		else {
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnim();
		}
	}
}

void UCustomGameInstance::SpawnReverseLoadingScreen()
{
	if (LoadingScreenSubclass) {
		if (!LoadingScreen) {
			LoadingScreen = CreateWidget<ULoadingScreen>(this, LoadingScreenSubclass);
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnimReverse();
		}
		else {
			LoadingScreen->AddToViewport(20);
			LoadingScreen->PlayFadeinAnimReverse();
		}
	}
}

void UCustomGameInstance::OpenLevel(FName LevelName)
{
	GetWorld()->GetTimerManager().SetTimer(SwitchLevelHandle, FTimerDelegate::CreateLambda([LevelName, this]() {
		UGameplayStatics::OpenLevel(this, LevelName);
	}), 1.0f, false);
}

