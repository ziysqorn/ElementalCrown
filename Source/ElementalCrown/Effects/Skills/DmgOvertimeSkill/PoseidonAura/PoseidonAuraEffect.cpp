#include "PoseidonAuraEffect.h"

APoseidonAuraEffect::APoseidonAuraEffect() : ADmgOvertimeSkillEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/PoseidonAura/Effect_Skill_PoseidonAura.Effect_Skill_PoseidonAura'"))
{
	EffectElement = CreateDefaultSubobject<UWater>(FName("EffectElement"));
	BuildupAmount = 1.0f;
	DelayTillCount = 0.8f;
	TimePerHit = 0.25f;
	FlipbookComponent->SetLooping(false);
}

void APoseidonAuraEffect::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorScale3D(FVector(1.5, 1, 2.0));
}

void APoseidonAuraEffect::ExecuteOverlap()
{
	GetWorldTimerManager().SetTimer(DamageHandle, FTimerDelegate::CreateUObject(this, &APoseidonAuraEffect::DamageOvertime), TimePerHit, true, DelayTillCount);
}

void APoseidonAuraEffect::DamageOvertime()
{
	TArray<AActor*> actors;
	this->GetOverlappingActors(actors, AActor::StaticClass());
	for (int i = 0; i < actors.Num(); ++i) {
		if (actors[i] && this->GetOwner() && actors[i] != this->GetOwner()) {
			if (ABaseCharacter* OwningCharacter = Cast<ABaseCharacter>(this->GetOwner())) {
				TSubclassOf<UDamageType> DamageType;
				if (EffectElement) {
					if (ABaseCharacter* Character = Cast<ABaseCharacter>(actors[i])) {
						ABossCharacter* BossCharacter = Cast<ABossCharacter>(Character);
						if (!BossCharacter) {
							Character->GetMovementComponent()->StopMovementImmediately();
							if (Character->GetCharacterState() != CharacterState::STUN)
								Character->SetCharacterState(CharacterState::AIRBORNE);
							Character->LaunchCharacter(FVector(0.0f, 0, 500.0f), true, true);
						}
						UGameplayStatics::ApplyDamage(Character, OwningCharacter->CalculatedDamage(SkillDamage), OwningCharacter->GetController(), this, DamageType);
						EffectElement->ApplyStatusEffect(Character, BuildupAmount);
					}
				}
			}
		}
	}
}
