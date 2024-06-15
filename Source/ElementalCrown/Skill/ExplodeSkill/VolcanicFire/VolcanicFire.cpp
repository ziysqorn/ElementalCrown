#include "VolcanicFire.h"

VolcanicFire::VolcanicFire() : ExplodeSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Explosion/VolcanicFireExplosion/VolcanicFireIcon.VolcanicFireIcon'"))
{
	this->SKillName = "Volcanic Fire";
	StunTime = 3.00f;
	SkillElement = new Fire();
}

VolcanicFire::~VolcanicFire()
{
}

void VolcanicFire::PerformSkill()
{
	int OwnerMana = OwningCharacter->GetCurrentMana();
	if (OwnerMana >= 0) {
		if (OwningCharacter && abs(OwningCharacter->GetVelocity().Z) <= 0.001f && isAvailable && OwnerMana > 0) {
			ExplodeSkill::PerformSkill();
			OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
			OwningCharacter->SetManaAfterConsume(ManaConsumption);
		}
	}
	else {
		if (OwningCharacter && abs(OwningCharacter->GetVelocity().Z) <= 0.001f && isAvailable) {
			ExplodeSkill::PerformSkill();
			OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
		}
	}
}