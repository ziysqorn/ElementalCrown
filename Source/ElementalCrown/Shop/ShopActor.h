// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../Skill/BaseSkill.h"
#include "../Consumable/Consumable.h"
#include "../CustomStructures/ShopData.h"
#include "../Interface/InteractableInterface.h"
#include "../UI/ShopUI/ShopUI.h"
#include "ShopActor.generated.h"

UCLASS()
class ELEMENTALCROWN_API AShopActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperFlipbookComponent* ShopFlipbook = nullptr;

	TArray<UConsumable*> AvailableConsumables;

	TArray<UBaseSkill*> AvailableSkills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Important | Shop data table")
	UDataTable* ShopDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Important | Shop UI subclass")
	TSubclassOf<UShopUI> ShopUISubclass;

	bool haveWelcomedPlayer = false;

	UPROPERTY()
	UShopUI* ShopUI = nullptr;

public:	
	// Sets default values for this actor's properties
	AShopActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LoadShopItem();

	void RefreshShopItem();

	void SaveGameplay(AActor* OtherActor);

	void SavePlayerInfo(AActor* OtherActor);

	void SaveGameProgress(AActor* OtherActor);

	void Interact(ACharacter* InteractedCharacter) override;

	UFUNCTION()
	virtual void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
