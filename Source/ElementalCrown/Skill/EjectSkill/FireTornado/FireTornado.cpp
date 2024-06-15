#include "FireTornado.h"

FireTornadoSkill::FireTornadoSkill() : EjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FireTornado/FireTonardoIcon.FireTonardoIcon'"))
{
	this->SKillName = "Fire Tornado";
	StunTime = 3.00f;
	SkillElement = new Fire();
}

void FireTornadoSkill::PerformSkill()
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
