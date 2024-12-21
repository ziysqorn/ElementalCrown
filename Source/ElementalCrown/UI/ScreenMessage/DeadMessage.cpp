// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadMessage.h"
#include "../../Controller/MainController.h"
#include "../../Characters/Main Character/MainCharacter.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

void UDeadMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Txt_Message->SetText(FText::FromString("YOU DIED"));
}

void UDeadMessage::NativeConstruct()
{
	Super::NativeConstruct();


}

void UDeadMessage::AnimEndAction()
{
	if (AMainController* MainController = this->GetOwningPlayer<AMainController>()) {
		if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
			CustomGameInstance->SpawnLoadingScreen();
			GetWorld()->GetTimerManager().SetTimer(ReloadLevelHandle, FTimerDelegate::CreateLambda([this, CustomGameInstance]() {
				CustomGameInstance->OpenLevel(FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
			}), 1.0f, false);
		}
	}
	this->RemoveFromParent();
}
