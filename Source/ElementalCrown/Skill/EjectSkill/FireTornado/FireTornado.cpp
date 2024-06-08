#include "FireTornado.h"

FireTornadoSkill::FireTornadoSkill() : EjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FireTornado/FireTonardoIcon.FireTonardoIcon'"))
{
	this->SKillName = "Fire Tornado";
	StunTime = 3.00f;
	SkillElement = new Fire();
}

void FireTornadoSkill::PerformSkill()
{
	if (abs(OwningCharacter->GetVelocity().Z) <= 0.001f && isAvailable) {
		EjectSkill::PerformSkill();
		if (OwningCharacter) {
			OwningCharacter->GetAnimInstance()->JumpToNode(FName("Fire Tornado"));
		}
	}

}
