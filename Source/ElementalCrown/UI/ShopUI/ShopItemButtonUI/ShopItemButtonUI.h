// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../ProjectIncludes.h"
#include "ShopItemButtonUI.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UShopItemButtonUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_ItemButton = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* Image_ItemAvt = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* Txt_ItemName = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* Txt_ItemPrice = nullptr;

	UPROPERTY()
	UObject* ManagedItem = nullptr;

public:
	void SetManagedObject(UObject* inObject) {
		if (inObject) ManagedItem = inObject;
	}
	void SetItemImage(UPaperSprite* Image) {
		if (Image) Image_ItemAvt->SetBrushResourceObject(Image);
	}

	void SetItemName(FText inText) {
		Txt_ItemName->SetText(inText);
	}

	void SetItemPrice(FText inText) {
		Txt_ItemPrice->SetText(inText);
	}
};
