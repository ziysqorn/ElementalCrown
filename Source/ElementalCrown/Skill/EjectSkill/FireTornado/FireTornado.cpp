#include "FireTornado.h"

FireTornadoSkill::FireTornadoSkill() : EjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FireTornado/FireTonardoIcon.FireTonardoIcon'"))
{
	this->SKillName = "Fire Tornado";
	StunTime = 3.00f;
	SkillElement = new Fire();
}
