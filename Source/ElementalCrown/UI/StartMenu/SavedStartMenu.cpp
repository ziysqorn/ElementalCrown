// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedStartMenu.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

void USavedStartMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_NewGame->OnClicked.AddDynamic(this, &USavedStartMenu::StartNewGame);
	Btn_Continue->OnClicked.AddDynamic(this, &USavedStartMenu::ContinueGame);
	Btn_QuitGame->OnClicked.AddDynamic(this, &USavedStartMenu::QuitGame);
	Btn_Options->OnClicked.AddDynamic(this, &USavedStartMenu::OpenOptionMenu);
	SetIsFocusable(true);
}

void USavedStartMenu::ContinueGame()
{
	if (UGameProgress* GameProgress = Cast<UGameProgress>(UGameplayStatics::LoadGameFromSlot("GameProgress", 0))) {
		FVector& PlayerLocation = GameProgress->GetPlayerLocation();
		FName& CurrentLevel = GameProgress->GetLevelName();
		if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
			CustomGameInstance->SpawnLoadingScreen();
			CustomGameInstance->OpenLevel(CurrentLevel);
		}
	}
}

void USavedStartMenu::StartNewGame()
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

void USavedStartMenu::OpenOptionMenu()
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

void USavedStartMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this->GetWorld(), nullptr, EQuitPreference::Quit, false);
}
