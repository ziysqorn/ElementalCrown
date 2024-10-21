#include "FireSlashWave.h"

AFireSlashWave::AFireSlashWave(): ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/FireSlashWave/Effect_Skill_FireSlashWave.Effect_Skill_FireSlashWave'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->MaxSpeed = 650;
		ProjectileMovement->InitialSpeed = 650;
		ProjectileMovement->ProjectileGravityScale = 0;
	}
	EffectElement = new Metal();
	this->OnActorBeginOverlap.AddDynamic(this, &AFireSlashWave::BeginOverlap);
}

void AFireSlashWave::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AFireSlashWaveExplode>(AFireSlashWaveExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}

