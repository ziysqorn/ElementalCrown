// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Elemental/ElementalSlot.h"
#include "Skill/SkillSlot.h"
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
	std::shared_ptr<CustomLinkedList<BaseSkill>> HUDSkillList;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UHorizontalBox* ElementalSlotBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Main character HUD", meta = (BindWidget))
	UHorizontalBox* SkillSlotBox = nullptr;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Elemental Slot SubClass")
	TSubclassOf<UElementalSlot> ElementalSlotSubClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Slot SubClass")
	TSubclassOf<USkillSlot> SkillSlotSubClass;
	UHorizontalBox* GetElementalSlotBox() { return ElementalSlotBox; }
	UHorizontalBox* GetSkillSlotBox() { return SkillSlotBox; }
	void SetupHUD();
	void SwitchedSlotHighlight(CustomNode<Elemental>* SwitchedNode);
	void SwitchedSlotHighlight(CustomNode<BaseSkill>* SwitchedNode);
	void RefreshSkillSlots(std::shared_ptr<CustomLinkedList<BaseSkill>> skillList);
};
