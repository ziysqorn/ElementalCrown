#include "AquaSphere.h"

AquaSphere::AquaSphere() : EjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/AquaSphere/WaterBall_-_Startup_and_Infinite_Sprite_8.WaterBall_-_Startup_and_Infinite_Sprite_8'"))
{
	this->SKillName = "Aqua Sphere";
	SkillElement = new Water();
}

AquaSphere::~AquaSphere()
{
}

void AquaSphere::PerformSkill()
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
