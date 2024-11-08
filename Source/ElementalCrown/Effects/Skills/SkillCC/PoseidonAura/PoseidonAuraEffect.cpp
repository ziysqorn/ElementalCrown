#include "PoseidonAuraEffect.h"

APoseidonAuraEffect::APoseidonAuraEffect() : ASkillCC(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/PoseidonAura/Effect_Skill_PoseidonAura.Effect_Skill_PoseidonAura'"))
{
	EffectElement = CreateDefaultSubobject<UWater>(FName("EffectElement"));
	BuildupAmount = 1.0f;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(0.0f, 0, 500.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &APoseidonAuraEffect::BeginOverlap);
}

void APoseidonAuraEffect::BeginPlay()
{
	ASkillCC::BeginPlay();
	this->SetActorScale3D(FVector(1.5, 1, 2.0));
}
