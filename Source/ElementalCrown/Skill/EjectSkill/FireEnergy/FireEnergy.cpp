#include "FireEnergy.h"

FireEnergy::FireEnergy() : EjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FireEnergy/FireEnergyIcon.FireEnergyIcon'"))
{
	this->SKillName = "Fire Energy";
	SkillElement = new Fire();
}

FireEnergy::~FireEnergy()
{
}

void FireEnergy::PerformSkill()
{
	if (isAvailable) {
		EjectSkill::PerformSkill();
		if (OwningCharacter) {
			OwningCharacter->GetAnimInstance()->JumpToNode(FName("Fire Energy"));
		}
	}
}
