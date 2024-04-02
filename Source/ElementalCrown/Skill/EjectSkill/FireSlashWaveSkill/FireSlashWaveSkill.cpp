#include "FireSlashWaveSkill.h"

FireSlashWaveSkill::FireSlashWaveSkill()
{
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
