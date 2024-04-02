#include "FireEnergy.h"

FireEnergy::FireEnergy()
{
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
