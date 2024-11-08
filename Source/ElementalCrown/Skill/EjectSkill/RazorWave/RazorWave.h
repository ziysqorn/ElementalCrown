#pragma once

#include "../EjectSkill.h"

class ELEMENTALCROWN_API RazorWaveSkill : public EjectSkill {
public:
	////Constructor
	RazorWaveSkill();
	void PerformSkill() override;
};