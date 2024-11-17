// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "ConsumableSlot.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UConsumableSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Consumable Frame", meta = (BindWidget))
	UBorder* ConsumableFrame = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Consumable Avt", meta = (BindWidget))
	UImage* ConsumableAvt = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quantity Text", meta = (BindWidget))
	UTextBlock* QuantityText = nullptr;

public:
	void SetQuantityText(const FText& inText) {
		QuantityText->SetText(inText);
	}
};
