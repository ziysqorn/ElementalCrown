#pragma once

#include "../EjectSkill.h"
#include "RazorWave.generated.h"

UCLASS()
class ELEMENTALCROWN_API URazorWaveSkill : public UEjectSkill {

	GENERATED_BODY()

public:
	////Constructor
	URazorWaveSkill();
	void PerformSkill() override;
};