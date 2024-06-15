#include "FireSlashWaveSkill.h"

FireSlashWaveSkill::FireSlashWaveSkill() : EjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FireSlashWave/FireSlashWaveIcon.FireSlashWaveIcon'"))
{
	this->SKillName = "Fire Slash Wave";
	SkillElement = new Fire();
}

FireSlashWaveSkill::~FireSlashWaveSkill()
{
}

void FireSlashWaveSkill::PerformSkill()
{
	int OwnerMana = OwningCharacter->GetCurrentMana();
	if (OwnerMana >= 0) {
		if (OwningCharacter && abs(OwningCharacter->GetVelocity().Z) <= 0.001f && isAvailable && OwnerMana > 0) {
			EjectSkill::PerformSkill();
			OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
			OwningCharacter->SetManaAfterConsume(ManaConsumption);
		}
	}
	else {
		if (OwningCharacter && abs(OwningCharacter->GetVelocity().Z) <= 0.001f && isAvailable) {
			EjectSkill::PerformSkill();
			OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
		}
	}
}
