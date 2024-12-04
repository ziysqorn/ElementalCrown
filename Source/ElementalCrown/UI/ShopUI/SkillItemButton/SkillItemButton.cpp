// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItemButton.h"
#include "../../../Characters/Main Character/MainCharacter.h"
#include "../ShopUI.h"
#include "../../../Controller/MainController.h"
#include "../../../CustomSave/GameplaySave.h"


FReply USkillItemButton::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton().GetFName().IsEqual("LeftMouseButton")) {
		if (AMainController* MainController = this->GetOwningPlayer<AMainController>()) {
			if (AMainCharacter* MainCharacter = MainController->GetPawn<AMainCharacter>()) {
				if (ManagedSkill) {
					if (USkillComponent* SkillComponent = MainCharacter->GetSkillComp()) {
						TArray<UBaseSkill*>& EquippedSkillList = (*SkillComponent->GetSkillList());
						if (EquippedSkillList.Num() < 4) {
							EquippedSkillList.Add(ManagedSkill);
							if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0))) {
								TArray<FName>& SavedOwnedSkills = GameplaySave->GetOwnedSkills();
								TArray<int>& EquippedSkillIdxList = GameplaySave->GetEquippedSkillIdxList();
								FString ManagedSkillNameString = ManagedSkill->GetSkillName().ToString().Replace(TEXT(" "), TEXT(""));
								int idx = SavedOwnedSkills.Find(FName(ManagedSkillNameString));
								if (idx != INDEX_NONE) {
									if (EquippedSkillIdxList.IsValidIndex(idx)) {
										EquippedSkillIdxList[idx] = EquippedSkillList.Num() - 1;
										UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
										SkillComponent->LoadSkill();
										if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
											MainHUD->RefreshSkillSlots(EquippedSkillList);
										}
										if (ParentShopUI) {
											ParentShopUI->RefreshEquipSkillBox();
										}
									}
								}
								return FReply::Handled();
							}
						}
					}
				}
			}
		}
	}
    return FReply::Unhandled();
}


void USkillItemButton::SetParentShopUI(UShopUI* inShopUI)
{
	if (inShopUI) ParentShopUI = inShopUI;
}