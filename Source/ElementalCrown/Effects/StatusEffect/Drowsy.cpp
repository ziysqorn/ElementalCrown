#include "Drowsy.h"

ADrowsy::ADrowsy() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Drowsy/Flipbook/StatusEffect_Drowsy.StatusEffect_Drowsy'"))
{
	if (MirroredFlipbookComp) MirroredFlipbookComp->SetLooping(true);
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(true);
}
