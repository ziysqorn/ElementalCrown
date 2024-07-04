#pragma once

#include "CoreMinimal.h"
#include "../SkillProjectile.h"
#include "../../../Explode/FireSlashWaveExplode/FireSlashWaveExplode.h"
#include "FireSlashWave.generated.h"

UCLASS()
class ELEMENTALCROWN_API AFireSlashWave : public ASkillProjectile {
	GENERATED_BODY()
public:
	//Constructor
	AFireSlashWave();
	void SpawnExplosion() override;
};