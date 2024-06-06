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
	if (isAvailable) {
		EjectSkill::PerformSkill();
		if (OwningCharacter) {
			OwningCharacter->GetAnimInstance()->JumpToNode(SKillName);
		}
	}
}
