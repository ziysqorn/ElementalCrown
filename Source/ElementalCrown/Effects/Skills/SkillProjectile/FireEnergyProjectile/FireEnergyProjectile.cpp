#include "FireEnergyProjectile.h"

AFireEnergyProjectile::AFireEnergyProjectile() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/FireEnergy/Effect_Skill_FireEnergy.Effect_Skill_FireEnergy'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 500;
		ProjectileMovement->MaxSpeed = 500;
	}
	OwningSkill = new FireEnergy();
	this->OnActorBeginOverlap.AddDynamic(this, &AFireEnergyProjectile::BeginOverlap);
}

void AFireEnergyProjectile::BeginPlay()
{
	ASkillProjectile::BeginPlay();
	this->SetActorScale3D(FVector(1.75, 1, 1.75));
}

void AFireEnergyProjectile::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AFireEnergyExplode>(AFireEnergyExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}

void AFireEnergyProjectile::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyDamage(OtherActor, OwningCharacter->CalculatedDamage(OwningSkill->GetSkillDamage()), OwningCharacter->GetController(), this, DamageType);
		}
		this->SpawnExplosion();
		this->Destroy();
	}
}
