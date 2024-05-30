// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "PaperSprite.h"
#include "PaperFlipbook.h"
#include "ElementalSlot.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UElementalSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "ElementalSlot", meta = (BindWidget))
	UBorder* ElementalFrame = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "ElementalSlot", meta = (BindWidget))
	UBorder* ElementalOutline = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "ElementalSlot", meta = (BindWidget))
	UImage* ElementalIcon = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "ElementalSprite | Fire")
	UPaperSprite* FireSprite = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "ElementalSprite | Water")
	UPaperSprite* WaterSprite = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "ElementalSprite | Earth")
	UPaperSprite* EarthSprite = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "ElementalSprite | Plant")
	UPaperSprite* PlantSprite = nullptr;
public:
	UImage* GetIcon() { return ElementalIcon; }
	void ShowOutline() {
		if (ElementalOutline) ElementalOutline->SetVisibility(ESlateVisibility::Visible);
	}
	void HideOutline() {
		if (ElementalOutline) ElementalOutline->SetVisibility(ESlateVisibility::Hidden);
	}
	UPaperSprite* GetElementalSprite(FName name) {
		if (name.IsEqual(FName("Fire"))) return FireSprite;
		else if (name.IsEqual(FName("Water"))) return WaterSprite;
		else if (name.IsEqual(FName("Earth"))) return EarthSprite;
		else if (name.IsEqual(FName("Plant"))) return PlantSprite;
		return nullptr;
	}
};
