#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Bleed.h"

/**
 *
 */

class ELEMENTALCROWN_API BleedStatus : public BaseStatusEffect {
protected:
	FTimerHandle ApplyDelayHandle;
public:
	BleedStatus();
	~BleedStatus() override;
	void ExecuteStatus() override;
};