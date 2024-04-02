#pragma once

#include "../EjectSkill.h"

class ELEMENTALCROWN_API FireTornadoSkill : public EjectSkill {
public:
	////Constructor
	FireTornadoSkill();
	////Destructor
	//~FireTornadoSkill();
	//Perform this skill
	void PerformSkill() override;
};