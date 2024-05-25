// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Elemental/ElementalSlot.h"
#include "MainCharacterHUB.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UMainCharacterHUB : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUB", meta = (BindWidget))
	UHorizontalBox* ElementalSlotBox = nullptr;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Character HUB SubClass")
	TSubclassOf<UMainCharacterHUB> MainHUBSubClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Elemental Slot SubClass")
	TSubclassOf<UElementalSlot> ElementalSlotSubClass;
	UHorizontalBox* GetElementalSlotBox() { return ElementalSlotBox; }
};
