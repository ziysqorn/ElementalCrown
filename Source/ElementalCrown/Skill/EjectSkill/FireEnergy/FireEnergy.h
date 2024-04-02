#pragma once

#include "../EjectSkill.h"
#include "../../../Effects/Skills/SkillProjectile/FireEnergyProjectile/FireEnergyProjectile.h"

class ELEMENTALCROWN_API FireEnergy : public EjectSkill {
public:
	FireEnergy();
	~FireEnergy();
	void PerformSkill() override;
};