#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"

/**
 *
 */

class ELEMENTALCROWN_API BleedStatus : public BaseStatusEffect {
protected:
	int BleedDamage = 1;
	float TimeBetweenEachHit = 1.5f;
	FTimerHandle EffectHandle;
public:
	BleedStatus();
	~BleedStatus() override;
	void ExecuteStatus() override;
};