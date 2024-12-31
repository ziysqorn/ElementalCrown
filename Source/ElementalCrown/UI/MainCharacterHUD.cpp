// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"
#include "../Characters/Main Character/MainCharacter.h"

void UMainCharacterHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMainCharacterHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainCharacterHUD::SetupHUD()
{
	if (this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			if (USkillComponent* SkillComponent = MainCharacter->GetSkillComp()) {
				SetupSkillSlotBox(*(SkillComponent->GetSkillList()));
				SwitchedSlotHighlight(0);
			}
			for (int i = 0; i < MainCharacter->GetLiveCount(); ++i) {
				if (LiveCountUISubclass) {
					if (UUserWidget* liveCount = CreateWidget<UUserWidget>(this, LiveCountUISubclass)) {
						HorBox_LiveCountSlotBox->AddChild(liveCount);
					}
				}
			}
			if (UConsumableComponent* ConsumableComponent = MainCharacter->GetConsumableComp()) {
				TArray<UConsumable*>& ConsumableList = ConsumableComponent->GetConsumableList();
				for (int i = 0; i < ConsumableList.Num(); ++i) {
					if (UConsumableSlot* ConsumableSlot = Cast<UConsumableSlot>(HorBox_ConsumableList->GetChildAt(i))) {
						ConsumableSlot->SetQuantityText(FText::FromString(FString::FromInt(*(ConsumableList[i]->GetCurrentQuant()))));
					}
				}
			}
			if(UGoldComponent* GoldComponent = MainCharacter->GetGoldComp())
				SetGoldText(FText::FromString(FString::FromInt(GoldComponent->GetCurrentGold())));
			ProgBar_HPBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetHealthPercentage"));
			ProgBar_ManaBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetManaPercentage"));
		}
	}
}


void UMainCharacterHUD::SetupSkillSlotBox(TArray<UBaseSkill*>& list)
{
	if (this->SkillSlotSubClass) {
		for (int i = 0; i < list.Num(); ++i) {
			USkillSlot* skillSlot = CreateWidget<USkillSlot>(this, this->SkillSlotSubClass);
			if (skillSlot) {
				UBaseSkill* CurSkill = list[i];
				skillSlot->GetIcon()->SetBrushResourceObject(Cast<UObject>(CurSkill->GetSkillSprite()));
				if (i != 0) {
					FMargin SlotMargin(10.0f, 0.0f, 0.0f, 0.0f);
					skillSlot->SetPadding(SlotMargin);
				}
				skillSlot->UpdateCountdownProgress(0.0f);
				skillSlot->HideLoadBorder();
				HorBox_SkillSlotBox->AddChildToHorizontalBox(skillSlot);
			}
		}
	}
}

void UMainCharacterHUD::UpdateSkillCountdownProgUI(UBaseSkill* Skill, const float& inPercentage)
{
	if (Skill && this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			if (USkillComponent* SkillComponent = Cast<USkillComponent>(MainCharacter->GetSkillComp())) {
				TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
				int idx = SkillComponent->FindSkill(Skill);
				if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[idx]))
					skillSlot->UpdateCountdownProgress(inPercentage);
			}
		}
	}
}

void UMainCharacterHUD::AddStatsEffectToVerBox(UUserWidget* StatsEffect)
{
	VerBox_StatusProgress->AddChildToVerticalBox(StatsEffect);
}

void UMainCharacterHUD::RemoveStatsEffectFromVerBox(int removedIdx)
{
	VerBox_StatusProgress->RemoveChildAt(removedIdx);
}


void UMainCharacterHUD::ShowSkillLoaderUI(UBaseSkill* Skill)
{
	if (Skill && this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			if (USkillComponent* SkillComponent = Cast<USkillComponent>(MainCharacter->GetSkillComp())) {
				TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
				int idx = SkillComponent->FindSkill(Skill);
				if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[idx])) skillSlot->ShowLoadBorder();
			}
		}
	}
}

void UMainCharacterHUD::HideSkillLoaderUI(UBaseSkill* Skill)
{
	if (Skill && this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			if (USkillComponent* SkillComponent = Cast<USkillComponent>(MainCharacter->GetSkillComp())) {
				TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
				int idx = SkillComponent->FindSkill(Skill);
				if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[idx])) {
					skillSlot->UpdateCountdownProgress(0.0f);
					skillSlot->HideLoadBorder();
				}
			}
		}
	}
}

void UMainCharacterHUD::SwitchedSlotHighlight(int SwitchedNodeId)
{
	if (this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			if (USkillComponent* SkillComponent = Cast<USkillComponent>(MainCharacter->GetSkillComp())) {
				TArray<UWidget*> slotArr = HorBox_SkillSlotBox->GetAllChildren();
				for (int i = 0; i < slotArr.Num(); ++i) {
					if (USkillSlot* skillSlot = Cast<USkillSlot>(slotArr[i])) {
						skillSlot->HideOutline();
						if (i == SwitchedNodeId) {
							skillSlot->ShowOutline();
							FString SkillName = SkillComponent->FindSkill(SwitchedNodeId)->GetSkillName().ToString();
							Txt_SkillName->SetText(FText::FromString(SkillName));
						}
					}
				}
			}
		}
	}
}

void UMainCharacterHUD::RefreshSkillSlots(TArray<UBaseSkill*>& list)
{
	HorBox_SkillSlotBox->ClearChildren();
	Txt_SkillName->SetText(FText::FromString(""));
	SetupSkillSlotBox(list);
	SwitchedSlotHighlight(0);
}
