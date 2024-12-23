#include "Stun.h"

AStun::AStun() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Stun/Flipbook/StatusEffect_Stun.StatusEffect_Stun'"))
{
	if (MirroredFlipbookComp) MirroredFlipbookComp->SetLooping(true);
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(true);
}
