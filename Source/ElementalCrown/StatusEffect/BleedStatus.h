#pragma once

#include "CoreMinimal.h"
#include "BaseStatusEffect.h"
#include "../Effects/StatusEffect/Bleed.h"
#include "BleedStatus.generated.h"

/**
 *
 */

UCLASS()
class ELEMENTALCROWN_API UBleedStatus : public UBaseStatusEffect 
{
	GENERATED_BODY()

protected:
	FTimerHandle ApplyDelayHandle;
public:
	UBleedStatus();
	void BeginDestroy() override;
	void ExecuteStatus() override;
	void BloodSoaking();
};