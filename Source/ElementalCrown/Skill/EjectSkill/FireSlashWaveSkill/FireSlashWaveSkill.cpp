#include "FireSlashWaveSkill.h"
#include "../../../Controller/MainController.h"
#include "../../../Characters/Main Character/MainCharacter.h"

UFireSlashWaveSkill::UFireSlashWaveSkill() : UEjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FireSlashWave/Red_Effect_Bullet_Impact_Explosion_32x32_Revert_Sprite_0.Red_Effect_Bullet_Impact_Explosion_32x32_Revert_Sprite_0'"))
{
	this->SKillName = "Fire Slash Wave";
	this->SkillPrice = 40;
}

void UFireSlashWaveSkill::PerformSkill()
{
	if (USkillComponent* SkillComponent = Cast<USkillComponent>(this->GetOuter())) {
		if (ABaseCharacter* OwningCharacter = SkillComponent->GetOwner<ABaseCharacter>()) {
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
					OwningCharacter->GetWorldTimerManager().SetTimer(this->CountdownProgHandle, FTimerDelegate::CreateLambda([this, OwningCharacter]() {
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
}
