#pragma once

#include "../EjectSkill.h"
#include "FireSlashWaveSkill.generated.h"

UCLASS()
class ELEMENTALCROWN_API UFireSlashWaveSkill : public UEjectSkill {

	GENERATED_BODY()

public:
	//Constructor
	UFireSlashWaveSkill();
	void PerformSkill() override;
};