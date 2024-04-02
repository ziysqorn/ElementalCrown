#pragma once

#include "../SkillProjectile.h"
#include "../../../Explode/FireSlashWaveExplode/FireSlashWaveExplode.h"
#include "../../../../Skill/EjectSkill/FireSlashWaveSkill/FireSlashWaveSkill.h"
#include "FireSlashWave.generated.h"

UCLASS()
class ELEMENTALCROWN_API AFireSlashWave : public ASkillProjectile {
	GENERATED_BODY()
public:
	//Constructor
	AFireSlashWave();
	void SpawnExplosion() override;
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};