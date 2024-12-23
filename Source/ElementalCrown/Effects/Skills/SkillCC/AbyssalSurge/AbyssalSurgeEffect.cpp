#include "AbyssalSurgeEffect.h"

AAbyssalSurgeEffect::AAbyssalSurgeEffect() : ASkillCCEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/AbyssalSurge/Effect_Skill_AbyssalSurge.Effect_Skill_AbyssalSurge'"))
{
	EffectElement = CreateDefaultSubobject<UWater>(FName("EffectElement"));
	BuildupAmount = 4.0f;
	SkillDamage = 5;
	FlipbookComponent->SetLooping(false);
	LaunchVector = FVector(300.0f, 0.0f, 300.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &AAbyssalSurgeEffect::BeginOverlap);
}

void AAbyssalSurgeEffect::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(1.5, 1, 1.5));
}