// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuUI.h"
#include "../../CustomGameInstance/CustomGameInstance.h"
#include "../OptionUI/OptionUI.h"

void UStartMenuUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Btn_NewGame->OnClicked.AddDynamic(this, &UStartMenuUI::StartNewGame);
	Btn_QuitGame->OnClicked.AddDynamic(this, &UStartMenuUI::QuitGame);
	Btn_Options->OnClicked.AddDynamic(this, &UStartMenuUI::OpenOptionMenu);
	SetIsFocusable(true);
}

void UStartMenuUI::StartNewGame()
{
	if (UGameProgress* GameProgress = Cast<UGameProgress>(UGameplayStatics::CreateSaveGameObject(UGameProgress::StaticClass()))) {
		FVector& PlayerLocation = GameProgress->GetPlayerLocation();
		FName& CurrentLevel = GameProgress->GetLevelName();
		PlayerLocation = FVector(0.0f, 0.0f, 0.0f);
		CurrentLevel = FName("Intro1");
		UGameplayStatics::DeleteGameInSlot("ShopSave", 0);
		UGameplayStatics::DeleteGameInSlot("GameplaySave", 0);
		UGameplayStatics::DeleteGameInSlot("PlayerInfoSave", 0);
		UGameplayStatics::DeleteGameInSlot("GameProgress", 0);
		UGameplayStatics::SaveGameToSlot(GameProgress, "GameProgress", 0);
		if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
			CustomGameInstance->SpawnLoadingScreen();
			CustomGameInstance->OpenLevel(CurrentLevel);
		}
		
	}
}

void UStartMenuUI::OpenOptionMenu()
{
	if (OptionUISubclass) {
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0)) {
			if (UOptionUI* OptionUI = CreateWidget<UOptionUI>(PlayerController, OptionUISubclass)) {
				OptionUI->SetOwningPlayer(PlayerController);
				OptionUI->AddToViewport(1);
				OptionUI->SetFocus();
			}
		}
	}
}

void UStartMenuUI::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this->GetWorld(), nullptr, EQuitPreference::Quit, false);
}
