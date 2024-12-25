// Fill out your copyright notice in the Description page of Project Settings.


#include "ConductLevelScript.h"
#include "../CustomGameInstance/CustomGameInstance.h"
#include "CineCameraActor.h"

void AConductLevelScript::BeginPlay()
{
	Super::BeginPlay();

	if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
		CustomGameInstance->SpawnReverseFlashScreen();
		if (ULoadingScreen* Screen = CustomGameInstance->GetFlashScreen()) {
			Screen->LoadingScreenEndDel.BindLambda([this]() {
				if (this) {
					if (BackgroundTheme) {
						UGameplayStatics::PlaySound2D(this, BackgroundTheme);
					}
					if (ScreenMessageSubclass) {
						if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
							if (UScreenMessage* ScreenMessage = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageSubclass)) {
								ScreenMessage->SetOwningPlayer(PlayerController);
								ScreenMessage->AddToViewport(1);
								ScreenMessage->PlayFadein();
							}
						}
					}
				}
			});
		}
	}
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		if (ACineCameraActor* CineCamera = Cast<ACineCameraActor>(UGameplayStatics::GetActorOfClass(this, ACineCameraActor::StaticClass()))) {
			PlayerController->SetViewTarget(CineCamera);
		}
		if (BackgroundSubclass && BrushObject) {
			if (ULoadingScreen* BackgroundUI = CreateWidget<ULoadingScreen>(PlayerController, BackgroundSubclass)) {
				BackgroundUI->AddToViewport(0);
				BackgroundUI->SetBackground(BrushObject);
				BackgroundUI->SetBackgroundColor(FLinearColor::White);
			}
		}

		if (!DialogueUI && DialogUISubclass) {
			DialogueUI = CreateWidget<UDialogueUI>(PlayerController, DialogUISubclass);
		}

		if (DialogueUI) {
			DialogueUI->DialogueEndDel.BindUObject(this, &AConductLevelScript::ConductDoneAction);
			DialogueUI->SetOwningPlayer(PlayerController);
			DialogueUI->SetDialogueLines(&DialogueLines);
			DialogueUI->AddToViewport(1);
			PlayerController->SetShowMouseCursor(false);
			FInputModeGameAndUI GameandUI;
			PlayerController->SetInputMode(GameandUI);
			DialogueUI->SetFocus();
		}
	}
}

void AConductLevelScript::ConductDoneAction()
{
	if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
		CustomGameInstance->SpawnFlashScreen();
		CustomGameInstance->OpenLevelAfterFlash(NextLevelName);
	}
}
