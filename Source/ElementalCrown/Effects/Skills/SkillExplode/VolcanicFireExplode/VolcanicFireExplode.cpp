// Fill out your copyright notice in the Description page of Project Settings.


#include "VolcanicFireExplode.h"

AVolcanicFireExplode::AVolcanicFireExplode() : ASkillExplode(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Explosion/VolcanicFireExplosion/Effect_Skill_VolcanicFireExplosion.Effect_Skill_VolcanicFireExplosion'"))
{
	this->OnActorBeginOverlap.AddDynamic(this, &AVolcanicFireExplode::BeginOverlap);
	OwningSkill = new VolcanicFire();
}

void AVolcanicFireExplode::BeginPlay()
{
	ASkillExplode::BeginPlay();
	this->SetActorScale3D(FVector(2, 1, 2));
	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
	}), this->Flipbook->GetTotalDuration(), false);
}

void AVolcanicFireExplode::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Yes sirrr"));
	if (this->GetOwner()) {
		if (OtherActor != this->GetOwner()) {
			if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
					TSubclassOf<UDamageType> DamageType;
					UGameplayStatics::ApplyDamage(OtherActor, OwningCharacter->CalculatedDamage(OwningSkill->GetSkillDamage()), OwningCharacter->GetController(), this, DamageType);
					if (APaperZDCharacter* OverlappedCharacter = Cast<APaperZDCharacter>(OtherActor)) {
						OverlappedCharacter->LaunchCharacter(FVector(0, 0, 300), false, false);
					}
			}
		}
	}
}
