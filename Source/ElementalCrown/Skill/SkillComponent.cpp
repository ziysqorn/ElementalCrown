#include "SkillComponent.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "../Controller/MainController.h"

void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(this->GetOwner())) {
		if (AMainController* MainController = Cast<AMainController>(MainCharacter->GetController())) {
			if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) MainHUD->SwitchedSlotHighlight(CurSkillId);
		}
	}
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
