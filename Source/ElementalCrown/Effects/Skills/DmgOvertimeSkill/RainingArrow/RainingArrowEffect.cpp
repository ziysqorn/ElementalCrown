#include "RainingArrowEffect.h"

ARainingArrowEffect::ARainingArrowEffect() : ADmgOvertimeSkillEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Skill/AquilarieRainingArrow/Effect_Skill_AquilarieRainingArrow.Effect_Skill_AquilarieRainingArrow'"))
{
	EffectElement = CreateDefaultSubobject<UPlant>(FName("EffectElement"));
	DelayTillCount = 0.0f;
	BuildupAmount = 1.0f;
	TimePerHit = 0.4f;
	FlipbookComponent->SetLooping(false);
}

void ARainingArrowEffect::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorScale3D(FVector(2.0f, 1.0f, 3.0f));
}
