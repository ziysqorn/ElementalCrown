// Fill out your copyright notice in the Description page of Project Settings.


#include "CongratulationsMessage.h"
#include "../../CustomGameInstance/CustomGameInstance.h"

void UCongratulationsMessage::AnimEndAction()
{
	if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
		CustomGameInstance->SpawnFlashScreen();
		CustomGameInstance->OpenLevelAfterFlash(FName("Ending"));
	}
}
