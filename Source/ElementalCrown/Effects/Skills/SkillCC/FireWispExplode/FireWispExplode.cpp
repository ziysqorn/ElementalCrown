// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWispExplode.h"

AFireWispExplode::AFireWispExplode() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/FireEnergyExplode/Effect_Skill_FireEnergyExplode.Effect_Skill_FireEnergyExplode'"))
{
	EffectElement = CreateDefaultSubobject<UFire>(FName("EffectElement"));
	BuildupAmount = 10.0f;
	FlipbookComponent->SetLooping(false);
	SkillDamage = 5;
	LaunchVector = FVector(500.0f, 0.0f, 100.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &AFireWispExplode::BeginOverlap);
}

void AFireWispExplode::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(3.0f, 1.0f, 3.0f));
}

void AFireWispExplode::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && this->GetOwner() && OtherActor != this->GetOwner()) {
		if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
			TSubclassOf<UDamageType> DamageType;
			if (EffectElement) {
				if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor)) {
					UGameplayStatics::ApplyDamage(Character, OwningCharacter->CalculatedDamage(SkillDamage), OwningCharacter->GetController(), this, DamageType);
					EffectElement->ApplyStatusEffect(Character, BuildupAmount);
				}
			}
		}
	}
}
