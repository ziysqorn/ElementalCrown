#include "FireTornado.h"

UFireTornadoSkill::UFireTornadoSkill() : UEjectSkill(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/Skill/FireTornado/FireTonardoIcon.FireTonardoIcon'"))
{
	this->SKillName = "Fire Tornado";
	this->SkillPrice = 45;
	ManaConsumption = 8;
}
