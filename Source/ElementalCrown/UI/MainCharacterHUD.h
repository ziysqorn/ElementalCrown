// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Elemental/ElementalSlot.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "MainCharacterHUD.generated.h"

/**
 * 
 */

UCLASS()
class ELEMENTALCROWN_API UMainCharacterHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	std::shared_ptr<CustomLinkedList<Elemental>> HUDElementalList;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UHorizontalBox* ElementalSlotBox = nullptr;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Elemental Slot SubClass")
	TSubclassOf<UElementalSlot> ElementalSlotSubClass;
	UHorizontalBox* GetElementalSlotBox() { return ElementalSlotBox; }
	void SetupHUD();
	void SwitchedSlotHighlight(CustomNode<Elemental>* SwitchedNode);
};
