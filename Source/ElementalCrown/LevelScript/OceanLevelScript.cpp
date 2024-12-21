// Fill out your copyright notice in the Description page of Project Settings.


#include "OceanLevelScript.h"
#include "GameFramework/PlayerStart.h"
#include "../CustomGameInstance/CustomGameInstance.h"

void AOceanLevelScript::BeginPlay()
{
	Super::BeginPlay();

	if (UGameProgress* GameProgress = Cast<UGameProgress>(UGameplayStatics::LoadGameFromSlot("GameProgress", 0))) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Map here"));
		FName& LevelName = GameProgress->GetLevelName();
		FVector& PlayerLoc = GameProgress->GetPlayerLocation();
		if (PlayerLoc == FVector(0.0f, 0.0f, 0.0f)) {
			if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass())) {
				PlayerLoc = PlayerStart->GetActorLocation();
			}
		}
		LevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));
		FActorSpawnParameters SpawnParams;
		if (MainCharSubclass && LevelTilemap) {
			if (AMainCharacter* MainCharacter = GetWorld()->SpawnActor<AMainCharacter>(MainCharSubclass, PlayerLoc, FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
				MainCharacter->GetTilemapComp()->SetTileMap(LevelTilemap);
				if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
					/*if (UCustomGameInstance* CustomGameInstance = GetWorld()->GetGameInstance<UCustomGameInstance>()) {
						CustomGameInstance->SpawnReverseLoadingScreen();
						if (ULoadingScreen* LoadingScreen = CustomGameInstance->GetLoadingScreen()) {
							LoadingScreen->LoadingScreenEndDel.BindLambda([MainCharacter, PlayerController]() {
								MainCharacter->EnableInput(PlayerController);
								});
						}
					}*/
					PlayerController->Possess(MainCharacter);
					//MainCharacter->DisableInput(PlayerController);
				}
			}

			UGameplayStatics::SaveGameToSlot(GameProgress, "GameProgress", 0);
		}
	}
}
