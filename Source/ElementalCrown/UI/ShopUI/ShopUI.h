// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../Consumable/Consumable.h"
#include "../../Skill/BaseSkill.h"
#include "../../Skill/SkillComponent.h"
#include "../ShopUI/ShopItemButtonUI/ShopItemButtonUI.h"
#include "../ShopUI/SkillItemButton/SkillItemButton.h"
#include "../ShopUI/EquippedSkillUI/EquippedSkillUI.h"
#include "ShopUI.generated.h"

/**
 * 
 */

UCLASS()
class ELEMENTALCROWN_API UShopUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher_ShopContent = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UVerticalBox* VerBox_ConsumablesList = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UScrollBox* ScrBox_AvailableSkillsList = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UScrollBox* ScrBox_OwnedSkillsList = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHorizontalBox* HorBox_EquippedSkills = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_ConsumableTab = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_SkillTab = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_CloseShop = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_PopoutSkill = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Important")
	TSubclassOf<UShopItemButtonUI> ShopItemUISubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important")
	TSubclassOf<USkillItemButton> SkillItemUISubclass;

	UPROPERTY(EditDefaultsOnly, Category = "Important")
	TSubclassOf<UEquippedSkillUI> EquippedSkillUISubclass;

public:
	UFUNCTION()
	void SwitchToConsumableTab() {
		WidgetSwitcher_ShopContent->SetActiveWidgetIndex(0);
	}

	UFUNCTION()
	void SwitchToSkillTab() {
		WidgetSwitcher_ShopContent->SetActiveWidgetIndex(1);
	}

	UFUNCTION()
	void PopoutSkill();

	UFUNCTION()
	void CloseShop();

	void SetupShopUI(TArray<UConsumable*>& ConsumableList, TArray<UBaseSkill*>& SkillsList);

	void RefreshEquipSkillBox();

	void RefreshShop();

	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
