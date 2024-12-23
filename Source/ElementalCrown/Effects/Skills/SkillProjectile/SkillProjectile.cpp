// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillProjectile.h"

// Sets default values
ASkillProjectile::ASkillProjectile()
{
}

ASkillProjectile::ASkillProjectile(const TCHAR* Ref) : ASkillEffect(Ref)
{
	if (!ProjectileMovement) {
		ProjectileMovement = this->CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
		//Initial projectile movement settings
		ProjectileMovement->InitialSpeed = 700;
		ProjectileMovement->MaxSpeed = 700;
		ProjectileMovement->ProjectileGravityScale = 0;
	}
}

// Called when the game starts or when spawned
void ASkillProjectile::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorScale3D(FVector(2, 1, 2));

	if (DestroyDelay > 0.00f) {
		GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateUObject(this, &ASkillProjectile::SelfDestroy), DestroyDelay, false);
	}
}

void ASkillProjectile::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && this->GetOwner() && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyDamage(OtherActor, OwningCharacter->CalculatedDamage(SkillDamage), OwningCharacter->GetController(), this, DamageType);
			if (EffectElement) {
				if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor)) {
					EffectElement->ApplyStatusEffect(Character, BuildupAmount);
				}
			}
		}
		else {
			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyDamage(OtherActor, SkillDamage, nullptr, this, DamageType);
			if (EffectElement) {
				if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor)) {
					EffectElement->ApplyStatusEffect(Character, BuildupAmount);
				}
			}
		}
		this->SpawnExplosion();
		this->Destroy();
	}
}

void ASkillProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionObjectType() == ECC_GameTraceChannel1) return;
	this->SpawnExplosion();
	this->Destroy();
}

