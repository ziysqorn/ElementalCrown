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
	if(abs(OwningCharacter->GetVelocity().Z) <= 0.0001f && isAvailable){
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Volcanic Fire"));
		ExplodeSkill::PerformSkill();
		if (OwningCharacter) {
			OwningCharacter->GetAnimInstance()->JumpToNode(FName("Volcanic Fire Skill"));
		}
	}
}