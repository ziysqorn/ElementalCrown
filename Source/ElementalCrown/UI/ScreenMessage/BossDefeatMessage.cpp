// Fill out your copyright notice in the Description page of Project Settings.


#include "BossDefeatMessage.h"
#include "../../Controller/MainController.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

void UBossDefeatMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UBossDefeatMessage::NativeConstruct()
{
	Super::NativeConstruct();

	FString Message = BossName.ToString().ToUpper() + FString(" DEFEATED");
	Txt_Message->SetText(FText::FromString(Message));
}

void UBossDefeatMessage::AnimEndAction()
{
	if (AMainController* MainController = this->GetOwningPlayer<AMainController>()) {
		if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
			CustomGameInstance->SpawnLoadingScreen();
			CustomGameInstance->OpenLevel(NextLevelName);
		}
	}
	this->RemoveFromParent();
}
