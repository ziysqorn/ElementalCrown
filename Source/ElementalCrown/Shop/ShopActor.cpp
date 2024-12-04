// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopActor.h"
#include "../CustomSave/ShopSave.h"
#include "../CustomSave/PlayerInfoSave.h"
#include "../CustomSave/GameplaySave.h"
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
		ShopUI->SetupShopUI(AvailableConsumables, AvailableSkills);
	}
}

void AShopActor::SaveGameplay(AActor* OtherActor)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
		if (UGameplayStatics::DoesSaveGameExist("GameplaySave", 0)) {
			if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0))) {
				TArray<FName>& SavedConsumable = GameplaySave->GetConsumableList();
				TArray<int>& SavedConsumableQuant = GameplaySave->GetConsumableQuantList();
				if (UConsumableComponent* ConsumableComp = MainCharacter->GetConsumableComp()) {
					TArray<UConsumable*>& ConsumableList = ConsumableComp->GetConsumableList();
					for (int i = 0; i < ConsumableList.Num(); ++i) {
						FString ConsumableNameString = ConsumableList[i]->GetConsumableName().ToString().Replace(TEXT(" "), TEXT(""));
						SavedConsumable.Add(FName(ConsumableNameString));
						SavedConsumableQuant.Add((*ConsumableList[i]->GetCurrentQuant()));
					}
				}
				TArray<FName>& SavedOwnedSkillList = GameplaySave->GetOwnedSkills();
				TArray<int>& SavedEquippedSkillIdxList = GameplaySave->GetEquippedSkillIdxList();
				UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
				haveWelcomedPlayer = true;
			}
		}
		else {
			if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::CreateSaveGameObject(UGameplaySave::StaticClass()))) {
				TArray<FName>& SavedConsumable = GameplaySave->GetConsumableList();
				TArray<int>& SavedConsumableQuant = GameplaySave->GetConsumableQuantList();
				if (UConsumableComponent* ConsumableComp = MainCharacter->GetConsumableComp()) {
					TArray<UConsumable*>& ConsumableList = ConsumableComp->GetConsumableList();
					for (int i = 0; i < ConsumableList.Num(); ++i) {
						FString ConsumableNameString = ConsumableList[i]->GetConsumableName().ToString().Replace(TEXT(" "), TEXT(""));
						SavedConsumable.Add(FName(ConsumableNameString));
						SavedConsumableQuant.Add((*ConsumableList[i]->GetCurrentQuant()));
					}
				}
				TArray<FName>& SavedOwnedSkillList = GameplaySave->GetOwnedSkills();
				TArray<int>& SavedEquippedSkillIdxList = GameplaySave->GetEquippedSkillIdxList();
				UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
				haveWelcomedPlayer = true;
			}
		}
	}
}

void AShopActor::SavePlayerInfo(AActor* OtherActor)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
		if (UGameplayStatics::DoesSaveGameExist("PlayerInfoSave", 0)) {
			if (UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::LoadGameFromSlot("PlayerInfoSave", 0))) {
				FVector& PlayerLocation = PlayerInfoSave->GetPlayerLocation();
				int* SavedGold = PlayerInfoSave->GetCurrentGold();
				int* SavedHealth = PlayerInfoSave->GetPlayerHealth();
				int* SavedMana = PlayerInfoSave->GetPlayerMana();
				PlayerLocation = this->GetActorLocation();
				*SavedHealth = (int)MainCharacter->GetCurrentHealth();
				*SavedMana = MainCharacter->GetCurrentMana();
				if (UGoldComponent* GoldComponent = MainCharacter->GetGoldComp()) {
					*SavedGold = GoldComponent->GetCurrentGold();
				}
				UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
				haveWelcomedPlayer = true;
			}
		}
		else if (UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::CreateSaveGameObject(UPlayerInfoSave::StaticClass()))) {
			FVector& PlayerLocation = PlayerInfoSave->GetPlayerLocation();
			int* SavedGold = PlayerInfoSave->GetCurrentGold();
			int* SavedHealth = PlayerInfoSave->GetPlayerHealth();
			int* SavedMana = PlayerInfoSave->GetPlayerMana();
			PlayerLocation = this->GetActorLocation();
			*SavedHealth = (int)MainCharacter->GetCurrentHealth();
			*SavedMana = MainCharacter->GetCurrentMana();
			if (UGoldComponent* GoldComponent = MainCharacter->GetGoldComp()) {
				*SavedGold = GoldComponent->GetCurrentGold();
			}
			UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
			haveWelcomedPlayer = true;
		}
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
					ShopUI->SetupShopUI(AvailableConsumables, AvailableSkills);
					ShopUI->AddToViewport(11);
					ShopUI->SetFocus();
					PlayerController->SetShowMouseCursor(true);
					InteractedCharacter->DisableInput(PlayerController);
				}
			}
		}
		else {
			if (ShopUI && InteractedCharacter) {
				LoadShopItem();
				ShopUI->SetupShopUI(AvailableConsumables, AvailableSkills);
				ShopUI->AddToViewport(11);
				ShopUI->SetFocus();
				PlayerController->SetShowMouseCursor(true);
				InteractedCharacter->DisableInput(PlayerController);
			}
		}
	}
}

void AShopActor::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!haveWelcomedPlayer) {
		SaveGameplay(OtherActor);
		SavePlayerInfo(OtherActor);
	}
}

