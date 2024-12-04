// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopItemButtonUI.h"
#include "../../../Characters/Main Character/MainCharacter.h"
#include "../../../CustomSave/PlayerInfoSave.h"
#include "../../../CustomSave/GameplaySave.h"
#include "../../../CustomSave/ShopSave.h"
#include "../../../Shop/ShopActor.h"
#include "../../../CustomStructures/ConsumableData.h"

void UShopItemButtonUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

FReply UShopItemButtonUI::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton().GetFName().IsEqual("LeftMouseButton")) {
		if (APlayerController* PlayerController = this->GetOwningPlayer()) {
			if (AMainCharacter* MainCharacter = PlayerController->GetPawn<AMainCharacter>()) {
				if (ManagedItem) {
					if (UConsumable* Consumable = Cast<UConsumable>(ManagedItem)) {
						if (UGoldComponent* GoldComponent = MainCharacter->GetGoldComp()) {
							if (Txt_ItemPrice->GetText().IsNumeric()) {
								int ItemPrice = FCString::Atoi(*(Txt_ItemPrice->GetText().ToString()));
								if (GoldComponent->HaveEnoughGoldToBuy(ItemPrice)) {
									if (UConsumableComponent* ConsumableComponent = MainCharacter->GetConsumableComp()) {
										if (ConsumableComponent->IsValidQuantityAfterAdding(Consumable->GetConsumableName(), 1)) {
											GoldComponent->ReduceGold(ItemPrice);
											int quantityAfterAdding = ConsumableComponent->AddPotionQuantity(Consumable->GetConsumableName(), 1);
											UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::LoadGameFromSlot("PlayerInfoSave", 0));
											UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0));
											if (PlayerInfoSave) {
												int* SavedGold = PlayerInfoSave->GetCurrentGold();
												*SavedGold -= ItemPrice;
												UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
											}
											if (GameplaySave) {
												FString ConsumableString = Consumable->GetConsumableName().ToString().Replace(TEXT(" "), TEXT(""));
												const TArray<FName>& ConsumableList = GameplaySave->GetConsumableList();
												int idx = ConsumableList.Find(FName(ConsumableString));
												if (idx != INDEX_NONE) {
													TArray<int>& QuantList = GameplaySave->GetConsumableQuantList();
													QuantList[idx] = quantityAfterAdding;
													UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
												}
											}
											return FReply::Handled();
										}
									}
								}
							}
						}
					}
					else if (UBaseSkill* Skill = Cast<UBaseSkill>(ManagedItem)) {
						if (USkillComponent* SkillComponent = MainCharacter->GetSkillComp()) {
							if (UGoldComponent* GoldComponent = MainCharacter->GetGoldComp()) {
								int ItemPrice = FCString::Atoi(*(Txt_ItemPrice->GetText().ToString()));
								if (GoldComponent->HaveEnoughGoldToBuy(ItemPrice)) {
									UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0));
									if (GameplaySave) {
										FString SkillString = Skill->GetSkillName().ToString().Replace(TEXT(" "), TEXT(""));
										TArray<FName>& OwnedSkillList = GameplaySave->GetOwnedSkills();
										TArray<int>& EquippedSkillIdxList = GameplaySave->GetEquippedSkillIdxList();
										int idx = OwnedSkillList.Find(FName(SkillString));
										if (idx != INDEX_NONE) return FReply::Unhandled();
										OwnedSkillList.Add(FName(SkillString));
										EquippedSkillIdxList.Add(-1);
										UGameplayStatics::SaveGameToSlot(GameplaySave, "GameplaySave", 0);
									}
									UPlayerInfoSave* PlayerInfoSave = Cast<UPlayerInfoSave>(UGameplayStatics::LoadGameFromSlot("PlayerInfoSave", 0));
									UShopSave* ShopSave = Cast<UShopSave>(UGameplayStatics::LoadGameFromSlot("ShopSave", 0));
									if (PlayerInfoSave) {
										int* SavedGold = PlayerInfoSave->GetCurrentGold();
										*SavedGold -= ItemPrice;
										GoldComponent->ReduceGold(ItemPrice);
										UGameplayStatics::SaveGameToSlot(PlayerInfoSave, "PlayerInfoSave", 0);
									}
									if (ShopSave) {
										FString SkillString = Skill->GetSkillName().ToString().Replace(TEXT(" "), TEXT(""));
										TArray<FName>& ShopSkillList = ShopSave->GetSavedAvailableSkills();
										ShopSkillList.RemoveSingle(FName(SkillString));
										UGameplayStatics::SaveGameToSlot(ShopSave, "ShopSave", 0);
									}
									SkillComponent->LoadSkill();
									if (AShopActor* Shop = Cast<AShopActor>(Skill->GetOuter())) {
										Shop->RefreshShopItem();
									}
									this->RemoveFromParent();
									this->ConditionalBeginDestroy();
									return FReply::Handled();
								}
							}
						}
					}
				}
			}
		}
	}
	return FReply::Unhandled();
}
