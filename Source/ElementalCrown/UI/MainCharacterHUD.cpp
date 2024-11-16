// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"
#include "../Characters/Main Character/MainCharacter.h"

void UMainCharacterHUD::SetupHUD()
{
	if (this->GetOwningPlayer()) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwningPlayer()->GetPawn())) {
			if (USkillComponent* SkillComponent = Cast<USkillComponent>(MainCharacter->GetSkillComp())) {
				SetupSkillSlotBox(*(SkillComponent->GetSkillList()));
				SetCoinText(FText::FromString(FString::FromInt(0)));
				ProgBar_HPBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetHealthPercentage"));
				ProgBar_ManaBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetManaPercentage"));
			}
		}
	}
}


void UMainCharacterHUD::SetupSkillSlotBox(TArray<BaseSkill*>& list)
{
	if (this->SkillSlotSubClass) {
		for (int i = 0; i < list.Num(); ++i) {
			USkillSlot* skillSlot = CreateWidget<USkillSlot>(this, this->SkillSlotSubClass);
			if (skillSlot) {
				BaseSkill* CurSkill = list[i];
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

void UMainCharacterHUD::UpdateSkillCountdownProgUI(BaseSkill* Skill, const float& inPercentage)
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


void UMainCharacterHUD::ShowSkillLoaderUI(BaseSkill* Skill)
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

void UMainCharacterHUD::HideSkillLoaderUI(BaseSkill* Skill)
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
							FString SkillName = SkillComponent->FindSkill(SwitchedNodeId)->GetName().ToString();
							Txt_SkillName->SetText(FText::FromString(SkillName));
						}
					}
				}
			}
		}
	}
}

void UMainCharacterHUD::RefreshSkillSlots(TArray<BaseSkill*>& list)
{
	if (HorBox_SkillSlotBox->HasAnyChildren()) {
		HorBox_SkillSlotBox->ClearChildren();
		SetupSkillSlotBox(list);
		SwitchedSlotHighlight(0);
	}
}

UBossHealthBar* UMainCharacterHUD::AddBossHealthbarToBox()
{
	UBossHealthBar* BossHealthbar = CreateWidget<UBossHealthBar>(this->GetOwningPlayer(), BossHealthbarSubclass);
	if(BossHealthbar) SizeBox_BossHealthbarBox->AddChild(BossHealthbar);
	return BossHealthbar;
}

void UMainCharacterHUD::RemoveBossHealthbarFromBox()
{
	SizeBox_BossHealthbarBox->RemoveChildAt(0);
}
