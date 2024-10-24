#include "Burn.h"

ABurn::ABurn() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Burn/Flipbook/StatusEffect_Burn_Main.StatusEffect_Burn_Main'"))
{
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(true);
}
