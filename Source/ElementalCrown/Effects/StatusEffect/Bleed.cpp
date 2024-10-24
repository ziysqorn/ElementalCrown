#include "Bleed.h"

ABleed::ABleed() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/Impact/AttackHit/Blood/Effect_Impact_AttackHit_Blood.Effect_Impact_AttackHit_Blood'"))
{
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(false);
}
