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
