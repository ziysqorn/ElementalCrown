#include "FirePillar.h"
#include "../../../Characters/Main Character/MainCharacter.h"
#include "../../../Controller/MainController.h"
#include "../../../Effects/Skills/SkillCC/FirePillar/FirePillarEffect.h"

FirePillar::FirePillar() : SkillCC(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FirePillar/Retro_Impact_Effect_Pack_5_A_Sprite_4.Retro_Impact_Effect_Pack_5_A_Sprite_4'"))
{
	this->SKillName = "Fire Pillar";
}


void FirePillar::PerformSkill()
{
	if (OwningCharacter) {
		int OwnerMana = OwningCharacter->GetCurrentMana();
		if (OwnerMana > 0) {
			if (isAvailable && abs(OwningCharacter->GetVelocity().Z) <= 0.001f) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = OwningCharacter;
				OwningCharacter->GetWorld()->SpawnActor<AFirePillarEffect>(AFirePillarEffect::StaticClass(), OwningCharacter->GetActorLocation() + FVector(0.0f, 0.0f, 90.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
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
				OwningCharacter->SetManaAfterConsume(ManaConsumption);

			}
		}
	}
}
