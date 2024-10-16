// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkill.h"
#include "../Controller/MainController.h"

// Sets default values
BaseSkill::BaseSkill()
{
}

BaseSkill::BaseSkill(const TCHAR* Ref)
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteRef(Ref);
	SkillSprite = SpriteRef.Object;
}

BaseSkill::~BaseSkill()
{
	if (SkillElement) {
		delete SkillElement;
		SkillElement = nullptr;
	}
}

void BaseSkill::PerformSkill()
{
	if (OwningCharacter) {
		int OwnerMana = OwningCharacter->GetCurrentMana();
		if (OwnerMana > 0) {
			if (isAvailable && abs(OwningCharacter->GetVelocity().Z) <= 0.001f) {
				OwningCharacter->SetCharacterState(CharacterState::USESKILL);
				if (AMainController* MainController = Cast<AMainController>(OwningCharacter->GetController())) {
					if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
						MainHUD->ShowSkillLoaderUI(this);
					}
				}
				this->isAvailable = false;
				OwningCharacter->GetWorldTimerManager().SetTimer(this->CountdownProgHandle, FTimerDelegate::CreateLambda([this]() {
					if (AMainController* MainController = Cast<AMainController>(OwningCharacter->GetController())) {
						if (UMainCharacterHUD* MainHUD = MainController->GetMainHUD()) {
							CurrentCooldown += 0.1f;
							if (CurrentCooldown > CooldownTime) {
								this->isAvailable = true;
								CurrentCooldown = 0.0f;
								MainHUD->HideSkillLoaderUI(this);
								OwningCharacter->GetWorldTimerManager().ClearTimer(CountdownProgHandle);
								return;
							}
							MainHUD->UpdateSkillCountdownProgUI(this, CurrentCooldown / CooldownTime);
						}
					}
					}), 0.1f, true);
				OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
				OwningCharacter->SetManaAfterConsume(ManaConsumption);

			}
		}
	}
}


