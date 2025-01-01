#include "RazorWave.h"
#include "../../../Controller/MainController.h"
#include "../../../Characters/Main Character/MainCharacter.h"

URazorWaveSkill::URazorWaveSkill() : UEjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/RazorWave/Purple_Effect_Bullet_Impact_Explosion_32x32_Sprite_1.Purple_Effect_Bullet_Impact_Explosion_32x32_Sprite_1'"))
{
	this->SKillName = "Razor Wave";
	this->SkillPrice = 45;
}

void URazorWaveSkill::PerformSkill()
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
					isAvailable = false;
					GetWorld()->GetTimerManager().SetTimer(CountdownProgHandle, FTimerDelegate::CreateUObject(this, &URazorWaveSkill::CooldownSkill), 0.1f, true);
					OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
					OwningCharacter->SetManaAfterConsume(ManaConsumption);

				}
			}
		}
	}
}
