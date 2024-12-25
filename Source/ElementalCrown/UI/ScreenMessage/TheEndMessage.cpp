// Fill out your copyright notice in the Description page of Project Settings.


#include "TheEndMessage.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

void UTheEndMessage::AnimEndAction()
{
	if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
		UGameplayStatics::DeleteGameInSlot("GameProgress", 0);
		CustomGameInstance->SpawnLoadingScreen();
		CustomGameInstance->OpenLevel(FName("StartLevel"));
	}
}
