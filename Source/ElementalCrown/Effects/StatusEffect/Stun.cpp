#include "Stun.h"

AStun::AStun() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Stun/Flipbook/StatusEffect_Stun.StatusEffect_Stun'"), false)
{
	StatusFlipbookComp->SetLooping(true);
}
