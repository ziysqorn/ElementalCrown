#include "SkillComponent.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"
#include "../SkillsIncludes.h"
#include "../CustomSave/GameplaySave.h"
#include "../CustomStructures/SkillData.h"

void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USkillComponent::ChangeSkill()
{
	if (CurSkillId == SkillList.Num() - 1) CurSkillId = 0;
	else {
		if (SkillList.IsValidIndex(CurSkillId + 1)) ++CurSkillId;
	}
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
		if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
			if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) MainHUD->SwitchedSlotHighlight(CurSkillId);
		}
	}
}

void USkillComponent::LoadSkill()
{
	OwnedSkillList.Empty();
	SkillList.Empty();
	if (UGameplayStatics::DoesSaveGameExist("GameplaySave", 0)) {
		if (UGameplaySave* GameplaySave = Cast<UGameplaySave>(UGameplayStatics::LoadGameFromSlot("GameplaySave", 0))) {
			if (DT_Skill) {
				const TArray<FName>& OwnedSkills = GameplaySave->GetOwnedSkills();
				TArray<int>& EquippedSkillsIdxList = GameplaySave->GetEquippedSkillIdxList();
				int EquippedSkillsListSize = 0;
				for (int i = 0; i < EquippedSkillsIdxList.Num(); ++i) {
					if (EquippedSkillsIdxList[i] > -1) ++EquippedSkillsListSize;
				}
				SkillList.Init(nullptr, EquippedSkillsListSize);
				for (int i = 0; i < OwnedSkills.Num(); ++i) {
					if (FSkillData* SkillData = DT_Skill->FindRow<FSkillData>(OwnedSkills[i], "Lookup")) {
						UBaseSkill* NewSkill = NewObject<UBaseSkill>(this, SkillData->DataClass);
						if (NewSkill) {
							this->AddOwnedSkill(NewSkill);
							if (EquippedSkillsIdxList.IsValidIndex(i) && EquippedSkillsIdxList[i] > -1 
								&& SkillList.IsValidIndex(EquippedSkillsIdxList[i]))
								SkillList[EquippedSkillsIdxList[i]] = NewSkill;
						}
					}
				}
			}
		}
	}
}
