#include "Bleed.h"

ABleed::ABleed() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Impact/AttackHit/Blood/Effect_Impact_AttackHit_Blood.Effect_Impact_AttackHit_Blood'"), false)
{
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(false);
}

void ABleed::BeginPlay()
{
	Super::BeginPlay();

	this->GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
		}), StatusFlipbookComp->GetFlipbook()->GetTotalDuration(), false);
}
