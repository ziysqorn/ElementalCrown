#pragma once

#include "../EjectSkill.h"

class ELEMENTALCROWN_API FireEnergy : public EjectSkill {
public:
	FireEnergy();
	~FireEnergy();
	void PerformSkill() override;
};