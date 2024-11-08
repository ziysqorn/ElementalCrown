#pragma once

#include "../EjectSkill.h"

class ELEMENTALCROWN_API FireSlashWaveSkill : public EjectSkill {
public:
	//Constructor
	FireSlashWaveSkill();
	void PerformSkill() override;
};