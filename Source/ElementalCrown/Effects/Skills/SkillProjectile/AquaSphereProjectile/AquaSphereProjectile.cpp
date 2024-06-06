// Fill out your copyright notice in the Description page of Project Settings.


#include "AquaSphereProjectile.h"

AAquaSphereProjectile::AAquaSphereProjectile() : ASkillProjectile(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/AquaSphere/Effect_Skill_AquaSphere.Effect_Skill_AquaSphere'"))
{
	if (ProjectileMovement) {
		ProjectileMovement->InitialSpeed = 500;
		ProjectileMovement->MaxSpeed = 500;
	}
	OwningSkill = new AquaSphere();
	this->OnActorBeginOverlap.AddDynamic(this, &AAquaSphereProjectile::BeginOverlap);
}

void AAquaSphereProjectile::BeginPlay()
{
	ASkillProjectile::BeginPlay();
	this->SetActorScale3D(FVector(1.75, 1, 1.75));
}

void AAquaSphereProjectile::SpawnExplosion()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotation = (this->GetActorForwardVector().X > 0) ? FRotator(0, 0, 0) : FRotator(0, 180, 0);
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AAquaSphereExplode>(AAquaSphereExplode::StaticClass(), this->GetActorLocation(), SpawnRotation, SpawnParams);
}

void AAquaSphereProjectile::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
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
