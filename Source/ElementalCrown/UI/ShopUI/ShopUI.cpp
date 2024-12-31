// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUI.h"
#include "../../Characters/Main Character/MainCharacter.h"
#include "../../Controller/MainController.h"
#include "../../CustomSave/GameplaySave.h"


void UShopUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_ConsumableTab->OnClicked.AddDynamic(this, &UShopUI::SwitchToConsumableTab);
	Btn_SkillTab->OnClicked.AddDynamic(this, &UShopUI::SwitchToSkillTab);
	Btn_CloseShop->OnClicked.AddDynamic(this, &UShopUI::CloseShop);
	Btn_PopoutSkill->OnClicked.AddDynamic(this, &UShopUI::PopoutSkill);
	SetIsFocusable(true);
}

void UShopUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetSwitcher_ShopContent) WidgetSwitcher_ShopContent->SetActiveWidgetIndex(0);

	if (VerBox_ConsumablesList) VerBox_ConsumablesList->ClearChildren();
	if (ScrBox_AvailableSkillsList) ScrBox_AvailableSkillsList->ClearChildren();
	if (ScrBox_OwnedSkillsList) ScrBox_OwnedSkillsList->ClearChildren();
	if (HorBox_EquippedSkills) HorBox_EquippedSkills->ClearChildren();
}


void UShopUI::CloseShop()
{
	this->RemoveFromParent();
	if (APlayerController* PlayerController = GetOwningPlayer()) {
		PlayerController->SetShowMouseCursor(false);
		if (PlayerController->GetPawn()) PlayerController->GetPawn()->EnableInput(PlayerController);
	}
}

void UShopUI::PopoutSkill()
{
	if (AMainController* MainController = GetOwningPlayer<AMainController>()) {
		if (AMainCharacter* MainCharacter = MainController->GetPawn<AMainCharacter>()) {
			if (USkillComponent* SkillComponent = MainCharacter->GetSkillComp()) {
				TArray<UBaseSkill*>& SkillList = (*SkillComponent->GetSkillList());
				if (SkillList.Num() > 0) {
					UBaseSkill* LastEquippedSkill = SkillList.Last(0);
					if (LastEquippedSkill) {
						FString SkillNameString = LastEquippedSkill->GetSkillName().ToString().Replace(TEXT(" "), TEXT(""));
						if (UGameplayStatics::DoesSaveGameExist("GameplaySave", 0)) {
							if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0))) {
								TArray<FName>& OwnedSkill = GameplaySave->GetOwnedSkills();
								TArray<int>& EquippedIdxSkillList = GameplaySave->GetEquippedSkillIdxList();
								int idx = OwnedSkill.Find(FName(SkillNameString));
								if (idx != INDEX_NONE) {
									if (EquippedIdxSkillList.IsValidIndex(idx)) {
										EquippedIdxSkillList[idx] = -1;
										UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
										SkillComponent->LoadSkill();
										this->RefreshEquipSkillBox();
										if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
											MainHUD->RefreshSkillSlots(SkillList);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void UShopUI::SetupShopUI(TArray<UConsumable*>& ConsumableList, TArray<UBaseSkill*>& SkillsList)
{
	if (ShopItemUISubclass && SkillItemUISubclass) {
		for (int i = 0; i < ConsumableList.Num(); ++i) {
			if (UShopItemButtonUI* ShopItemUI = CreateWidget<UShopItemButtonUI>(this->GetWorld(), ShopItemUISubclass)) {
				if (i > 0) {
					ShopItemUI->SetPadding(FMargin(0.0f, 10.0f, 0.0f, 0.0f));
				}
				ShopItemUI->SetItemImage(ConsumableList[i]->GetAvatar());
				ShopItemUI->SetItemName(FText::FromName(ConsumableList[i]->GetConsumableName()));
				ShopItemUI->SetItemPrice(FText::FromString(FString::FromInt(ConsumableList[i]->GetPrice())));
				ShopItemUI->SetManagedObject(ConsumableList[i]);
				VerBox_ConsumablesList->AddChildToVerticalBox(ShopItemUI);
			}
		}
		for (int i = 0; i < SkillsList.Num(); ++i) {
			if (UShopItemButtonUI* ShopItemUI = CreateWidget<UShopItemButtonUI>(this->GetWorld(), ShopItemUISubclass)) {
				if (i > 0) {
					ShopItemUI->SetPadding(FMargin(0.0f, 10.0f, 0.0f, 0.0f));
				}
				ShopItemUI->SetItemImage(SkillsList[i]->GetSkillSprite());
				ShopItemUI->SetItemName(FText::FromName(SkillsList[i]->GetSkillName()));
				ShopItemUI->SetItemPrice(FText::FromString(FString::FromInt(SkillsList[i]->GetPrice())));
				ShopItemUI->SetManagedObject(SkillsList[i]);
				ScrBox_AvailableSkillsList->AddChild(ShopItemUI);
			}
		}

		if (APlayerController* PlayerController = GetOwningPlayer()) {
			if (ABaseCharacter* BaseCharacter = PlayerController->GetPawn<ABaseCharacter>()) {
				if (USkillComponent* SkillComponent = BaseCharacter->GetSkillComp()) {
					TArray<UBaseSkill*>& OwnedSkill = (*SkillComponent->GetOwnedSkillList());
					for (int i = 0; i < OwnedSkill.Num(); ++i) {
						if (USkillItemButton* SkillItemUI = CreateWidget<USkillItemButton>(this->GetWorld(), SkillItemUISubclass)) {
							if (i > 0) {
								SkillItemUI->SetPadding(FMargin(0.0f, 10.0f, 0.0f, 0.0f));
							}
							SkillItemUI->SetItemImage(OwnedSkill[i]->GetSkillSprite());
							SkillItemUI->SetItemName(FText::FromName(OwnedSkill[i]->GetSkillName()));
							SkillItemUI->SetManagedSkill(OwnedSkill[i]);
							SkillItemUI->SetParentShopUI(this);
							if (SkillComponent->FindSkill(OwnedSkill[i]) != INDEX_NONE) SkillItemUI->SetIsEnabled(false);
							else SkillItemUI->SetIsEnabled(true);
							ScrBox_OwnedSkillsList->AddChild(SkillItemUI);
						}
					}

					TArray<UBaseSkill*>& EquippedSkill = (*SkillComponent->GetSkillList());
					for (int i = 0; i < 4; ++i) {
						if (UEquippedSkillUI* EquippedSkillUI = CreateWidget<UEquippedSkillUI>(this->GetWorld(), EquippedSkillUISubclass)) {
							if (i > 0) {
								EquippedSkillUI->SetPadding(FMargin(30.0f, 0.0f, 0.0f, 0.0f));
							}

							if (EquippedSkill.IsValidIndex(i)) {
								EquippedSkillUI->SetItemImageVisible(ESlateVisibility::Visible);
								EquippedSkillUI->SetItemImage(EquippedSkill[i]->GetSkillSprite());
								EquippedSkillUI->SetManagedSkill(EquippedSkill[i]);
							}
							else EquippedSkillUI->SetItemImageVisible(ESlateVisibility::Hidden);
							HorBox_EquippedSkills->AddChildToHorizontalBox(EquippedSkillUI);
						}
					}
				}
			}
		}

	}
}

void UShopUI::RefreshEquipSkillBox()
{
	if(ScrBox_OwnedSkillsList) ScrBox_OwnedSkillsList->ClearChildren();
	if(HorBox_EquippedSkills) HorBox_EquippedSkills->ClearChildren();
	if (APlayerController* PlayerController = GetOwningPlayer()) {
		if (ABaseCharacter* BaseCharacter = PlayerController->GetPawn<ABaseCharacter>()) {
			if (USkillComponent* SkillComponent = BaseCharacter->GetSkillComp()) {
				TArray<UBaseSkill*>& OwnedSkill = (*SkillComponent->GetOwnedSkillList());
				for (int i = 0; i < OwnedSkill.Num(); ++i) {
					if (USkillItemButton* SkillItemUI = CreateWidget<USkillItemButton>(this->GetWorld(), SkillItemUISubclass)) {
						if (i > 0) {
							SkillItemUI->SetPadding(FMargin(0.0f, 10.0f, 0.0f, 0.0f));
						}
						SkillItemUI->SetItemImage(OwnedSkill[i]->GetSkillSprite());
						SkillItemUI->SetItemName(FText::FromName(OwnedSkill[i]->GetSkillName()));
						SkillItemUI->SetManagedSkill(OwnedSkill[i]);
						SkillItemUI->SetParentShopUI(this);
						if (SkillComponent->FindSkill(OwnedSkill[i]) != INDEX_NONE) SkillItemUI->SetIsEnabled(false);
						else SkillItemUI->SetIsEnabled(true);
						ScrBox_OwnedSkillsList->AddChild(SkillItemUI);
					}
				}

				TArray<UBaseSkill*>& EquippedSkill = (*SkillComponent->GetSkillList());
				for (int i = 0; i < 4; ++i) {
					if (UEquippedSkillUI* EquippedSkillUI = CreateWidget<UEquippedSkillUI>(this->GetWorld(), EquippedSkillUISubclass)) {
						if (i > 0) {
							EquippedSkillUI->SetPadding(FMargin(30.0f, 0.0f, 0.0f, 0.0f));
						}

						if (EquippedSkill.IsValidIndex(i)) {
							EquippedSkillUI->SetItemImageVisible(ESlateVisibility::Visible);
							EquippedSkillUI->SetItemImage(EquippedSkill[i]->GetSkillSprite());
							EquippedSkillUI->SetManagedSkill(EquippedSkill[i]);
						}
						else EquippedSkillUI->SetItemImageVisible(ESlateVisibility::Hidden);
						HorBox_EquippedSkills->AddChildToHorizontalBox(EquippedSkillUI);
					}
				}
			}
		}
	}
}

void UShopUI::RefreshShop()
{
	if (VerBox_ConsumablesList) VerBox_ConsumablesList->ClearChildren();
	if (ScrBox_AvailableSkillsList) ScrBox_AvailableSkillsList->ClearChildren();
	if (ScrBox_OwnedSkillsList) ScrBox_OwnedSkillsList->ClearChildren();
	if (HorBox_EquippedSkills) HorBox_EquippedSkills->ClearChildren();
}

FReply UShopUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().GetFName().IsEqual("Escape")) {
		CloseShop();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}
