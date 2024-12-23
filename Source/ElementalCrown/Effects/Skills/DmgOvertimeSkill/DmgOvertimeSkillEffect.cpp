// Fill out your copyright notice in the Description page of Project Settings.


#include "DmgOvertimeSkillEffect.h"

ADmgOvertimeSkillEffect::ADmgOvertimeSkillEffect()
{

}

ADmgOvertimeSkillEffect::ADmgOvertimeSkillEffect(const TCHAR* Ref) : ASkillEffect(Ref)
{
}

void ADmgOvertimeSkillEffect::BeginPlay()
{
	Super::BeginPlay();

	if (Flipbook) {
		ExecuteOverlap();
		GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateUObject(this, &ADmgOvertimeSkillEffect::SelfDestroy), Flipbook->GetTotalDuration(), false);
	}
}

void ADmgOvertimeSkillEffect::DamageOvertime()
{
	TArray<AActor*> actors;
	this->GetOverlappingActors(actors, AActor::StaticClass());
	for (int i = 0; i < actors.Num(); ++i) {
		if (actors[i] && this->GetOwner() && actors[i] != this->GetOwner()) {
			if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
				TSubclassOf<UDamageType> DamageType;
				UGameplayStatics::ApplyDamage(actors[i], SkillDamage, OwningCharacter->GetController(), this, DamageType);
				if (EffectElement) {
					if (ABaseCharacter* Character = Cast<ABaseCharacter>(actors[i])) {
						EffectElement->ApplyStatusEffect(Character, BuildupAmount);
					}
				}
			}
		}
	}
}

void ADmgOvertimeSkillEffect::ExecuteOverlap()
{
	GetWorldTimerManager().SetTimer(DamageHandle, FTimerDelegate::CreateUObject(this, &ADmgOvertimeSkillEffect::DamageOvertime), TimePerHit, true, DelayTillCount);
}

void ADmgOvertimeSkillEffect::SelfDestroy()
{
	this->Destroy();
}
