// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuUI.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

void UPauseMenuUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Resume->OnClicked.AddDynamic(this, &UPauseMenuUI::ResumeClick);
	Btn_ReturnToMenu->OnClicked.AddDynamic(this, &UPauseMenuUI::ReturnToMenuClick);
	SetIsFocusable(true);
}

FReply UPauseMenuUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().GetFName().IsEqual("Escape")) {
		CloseMenu();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UPauseMenuUI::ResumeClick()
{
	CloseMenu();
}

void UPauseMenuUI::ReturnToMenuClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("StartLevel"));
}

void UPauseMenuUI::CloseMenu()
{
	if (APlayerController* PlayerController = this->GetOwningPlayer()) {
		PlayerController->SetShowMouseCursor(false);
		if (PlayerController->GetPawn()) PlayerController->GetPawn()->EnableInput(PlayerController);
		UGameplayStatics::SetGlobalTimeDilation(this->GetWorld(), 1.0f);
		RemoveFromParent();
	}
}
