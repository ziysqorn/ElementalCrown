#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Bleed.h"
#include "BleedStatus.generated.h"

/**
 *
 */

UCLASS()
class ELEMENTALCROWN_API UBleedStatus : public UBaseStatusEffect {
	GENERATED_BODY()
public:
	UBleedStatus();
	void ExecuteStatus() override;
};