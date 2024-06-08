// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillExplode.h"

// Sets default values
ASkillExplode::ASkillExplode()
{
}

ASkillExplode::ASkillExplode(const TCHAR* Ref) : ASkillEffect(Ref)
{
}

// Called when the game starts or when spawned
void ASkillExplode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillExplode::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && this->GetOwner() && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			UGameplayStatics::ApplyDamage(OtherActor, SkillDamage, OwningCharacter->GetController(), this, DamageType);
		}
	}
}
