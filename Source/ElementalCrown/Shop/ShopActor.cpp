// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopActor.h"
#include "../CustomSave/ShopSave.h"
#include "../CustomSave/PlayerInfoSave.h"
#include "../CustomSave/GameplaySave.h"
#include "../CustomSave/GameProgress.h"
#include "../Characters/Main Character/MainCharacter.h"

// Sets default values
AShopActor::AShopActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	ShopFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("ShopFlipbook"));
	SceneComponent->SetupAttachment(RootComponent);
	ShopFlipbook->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AShopActor::BeginPlay()
{
	Super::BeginPlay();

	this->OnActorBeginOverlap.AddDynamic(this, &AShopActor::BeginOverlap);
}

void AShopActor::LoadShopItem()
{
	if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("ShopSave")), 0)) {
		if (UShopSave* ShopSave = Cast<UShopSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("ShopSave")), 0))) {
			if (ShopDataTable) {
				TArray<FName>& SavedConsumables = ShopSave->GetSavedConsumables();
				TArray<FName>& SavedSkills = ShopSave->GetSavedAvailableSkills();
				AvailableConsumables.Empty();
				AvailableSkills.Empty();
				for (int i = 0; i < SavedConsumables.Num(); ++i) {
					FShopData* DataRow = ShopDataTable->FindRow<FShopData>(SavedConsumables[i], TEXT("Lookup"));
					if (DataRow) AvailableConsumables.Add(NewObject<UConsumable>(this, DataRow->DataClass));
				}
				for (int i = 0; i < SavedSkills.Num(); ++i) {
					FShopData* DataRow = ShopDataTable->FindRow<FShopData>(SavedSkills[i], TEXT("Lookup"));
					if (DataRow) AvailableSkills.Add(NewObject<UBaseSkill>(this, DataRow->DataClass));
				}
			}
		}
	}
	else {
		if (ShopDataTable) {
			const TArray<FName>& RowNames = ShopDataTable->GetRowNames();
			if (UShopSave* ShopSave = Cast<UShopSave>(UGameplayStatics::CreateSaveGameObject(UShopSave::StaticClass()))) {
				AvailableConsumables.Empty();
				AvailableSkills.Empty();
				TArray<FName>& SavedConsumables = ShopSave->GetSavedConsumables();
				TArray<FName>& SavedSkills = ShopSave->GetSavedAvailableSkills();
				for (int i = 0; i < RowNames.Num(); ++i) {
					if (i >= 0 && i < 7) {
						SavedConsumables.Add(RowNames[i]);
						FShopData* DataRow = ShopDataTable->FindRow<FShopData>(RowNames[i], TEXT("Lookup"));
						if (DataRow) AvailableConsumables.Add(NewObject<UConsumable>(this, DataRow->DataClass));
					}
					else {
						SavedSkills.Add(RowNames[i]);
						FShopData* DataRow = ShopDataTable->FindRow<FShopData>(RowNames[i], TEXT("Lookup"));
						if (DataRow) AvailableSkills.Add(NewObject<UBaseSkill>(this, DataRow->DataClass));
					}
				}
				UGameplayStatics::SaveGameToSlot(ShopSave, TEXT("ShopSave"), 0);
			}
		}
	}
}

void AShopActor::RefreshShopItem()
{
	if (ShopUI) {
		LoadShopItem();
		ShopUI->RefreshShop();
		ShopUI->SetupShopUI(AvailableConsumables, AvailableSkills);
	}
}

void AShopActor::SaveGameplay(AActor* OtherActor)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
		MainCharacter->SaveGameplay();
	}
}

void AShopActor::SavePlayerInfo(AActor* OtherActor)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
		MainCharacter->SavePlayerInfo();
	}
}

void AShopActor::SaveGameProgress(AActor* OtherActor)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
		MainCharacter->SaveGameProgress(FName(UGameplayStatics::GetCurrentLevelName(GetWorld())), this->GetActorLocation());
	}
}

void AShopActor::Interact(ACharacter* InteractedCharacter)
{
	if (APlayerController* PlayerController = InteractedCharacter->GetController<APlayerController>()) {
		if (!IsValid(ShopUI)) {
			if (ShopUISubclass) {
				ShopUI = CreateWidget<UShopUI>(PlayerController, ShopUISubclass);
				if (IsValid(ShopUI) && InteractedCharacter) {
					LoadShopItem();
					ShopUI->AddToViewport(11);
					ShopUI->SetFocus();
					PlayerController->SetShowMouseCursor(true);
					InteractedCharacter->DisableInput(PlayerController);
					ShopUI->SetupShopUI(AvailableConsumables, AvailableSkills);
				}
			}
		}
		else {
			if (ShopUI && InteractedCharacter) {
				LoadShopItem();
				ShopUI->AddToViewport(11);
				ShopUI->SetFocus();
				PlayerController->SetShowMouseCursor(true);
				InteractedCharacter->DisableInput(PlayerController);
				ShopUI->SetupShopUI(AvailableConsumables, AvailableSkills);
			}
		}
	}
}

void AShopActor::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!haveWelcomedPlayer) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
			if (UStatusEffectComponent* StatusComp = MainCharacter->GetStatusEffectComp()) {
				StatusComp->ClearAllStatusEffect();
			}
		}
		SaveGameplay(OtherActor);
		SavePlayerInfo(OtherActor);
		SaveGameProgress(OtherActor);
		haveWelcomedPlayer = true;
	}
}

