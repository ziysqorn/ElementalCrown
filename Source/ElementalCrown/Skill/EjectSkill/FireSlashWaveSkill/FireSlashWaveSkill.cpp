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
	if (isAvailable) {
		EjectSkill::PerformSkill();
		if (OwningCharacter) {
			OwningCharacter->GetAnimInstance()->JumpToNode(FName("Fire Slash Wave"));
		}
	}
}
