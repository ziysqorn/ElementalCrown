#pragma once

#include "../SkillCC.h"
#include "FirePillar.generated.h"

UCLASS()
class ELEMENTALCROWN_API UFirePillar : public USkillCC {

	GENERATED_BODY()

public:
	UFirePillar();
	void PerformSkill() override;
};