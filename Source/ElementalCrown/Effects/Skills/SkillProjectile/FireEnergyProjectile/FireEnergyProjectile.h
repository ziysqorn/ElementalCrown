#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "../../../Explode/FireEnergyExplode/FireEnergyExplode.h"
#include "FireEnergyProjectile.generated.h"

UCLASS()
class ELEMENTALCROWN_API AFireEnergyProjectile : public ASkillProjectile {
	GENERATED_BODY()
public:
	AFireEnergyProjectile();
	void BeginPlay() override;
	void SpawnExplosion() override;
};