#include "FireTornado.h"

FireTornadoSkill::FireTornadoSkill()
{
	StunTime = 3.00f;
	SkillDamage = 4;
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
