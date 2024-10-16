#include "VolcanicFire.h"

VolcanicFire::VolcanicFire() : ExplodeSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Explosion/VolcanicFireExplosion/VolcanicFireIcon.VolcanicFireIcon'"))
{
	this->SKillName = "Volcanic Fire";
	StunTime = 3.00f;
}

VolcanicFire::~VolcanicFire()
{
}