#include "VolcanicFire.h"

VolcanicFire::VolcanicFire()
{
	StunTime = 3.00f;
	SkillDamage = 5;
}

VolcanicFire::~VolcanicFire()
{
}

void VolcanicFire::PerformSkill()
{
	if(abs(OwningCharacter->GetVelocity().Z) <= 0.0001f && isAvailable){
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Volcanic Fire"));
		ExplodeSkill::PerformSkill();
		if (OwningCharacter) {
			OwningCharacter->GetAnimInstance()->JumpToNode(FName("Volcanic Fire Skill"));
		}
	}
}