// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopActor.h"
#include "../CustomSave/ShopSave.h"

// Sets default values
AShopActor::AShopActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShopActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("ShopSave")), 0)) {
		if (UShopSave* ShopSave = Cast<UShopSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("ShopSave")), 0))) {
			AvailableConsumables = ShopSave->GetSavedConsumables();
		}
	}
	else {

	}
}

