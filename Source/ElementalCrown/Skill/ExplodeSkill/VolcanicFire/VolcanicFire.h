#pragma once

#include "../ExplodeSkill.h"

class ELEMENTALCROWN_API VolcanicFire : public ExplodeSkill {
protected:
	uint8 SpawnTimes{ 1 };
	//Spawn explosion timer handle
	FTimerHandle SpawnHandle;
public:
	VolcanicFire();
	~VolcanicFire();
	void PerformSkill() override;
};
