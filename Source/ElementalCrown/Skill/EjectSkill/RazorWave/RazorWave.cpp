#include "RazorWave.h"
#include "../../../Controller/MainController.h"
#include "../../../Characters/Main Character/MainCharacter.h"

RazorWaveSkill::RazorWaveSkill() : EjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/RazorWave/Purple_Effect_Bullet_Impact_Explosion_32x32_Sprite_1.Purple_Effect_Bullet_Impact_Explosion_32x32_Sprite_1'"))
{
	this->SKillName = "Razor Wave";
}

void RazorWaveSkill::PerformSkill()
{
	if (OwningCharacter) {
		int OwnerMana = OwningCharacter->GetCurrentMana();
		if (OwnerMana > 0) {
			if (isAvailable) {
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
