// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UI/MainCharacterHUD.h"
#include "../UI/ShopUI/ShopUI.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AMainController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main HUD sub class")
	TSubclassOf<UMainCharacterHUD> MainHUDSubClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shop UI subclass")
	TSubclassOf<UShopUI> ShopUISubClass;

	UShopUI* ShopUI = nullptr;

	UMainCharacterHUD* MainHUD = nullptr;
public:
	void BeginPlay() override;
	void OpenShop();
	UMainCharacterHUD* GetMainHUD() { return MainHUD; }
};
