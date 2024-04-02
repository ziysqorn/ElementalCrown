#pragma once

#include "../EjectSkill.h"
#include "../../../Effects/Skills/SkillProjectile/FireSlashWave/FireSlashWave.h"

class ELEMENTALCROWN_API FireSlashWaveSkill : public EjectSkill {
public:
	//Constructor
	FireSlashWaveSkill();
	//Destructor
	~FireSlashWaveSkill();
	//Perform this skill
	void PerformSkill() override;
};