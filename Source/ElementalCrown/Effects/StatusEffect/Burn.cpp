#include "Burn.h"

ABurn::ABurn() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Burn/Flipbook/StatusEffect_Burn_Main.StatusEffect_Burn_Main'"))
{
	if (MirroredFlipbookComp) MirroredFlipbookComp->SetLooping(true);
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(true);
}

void ABurn::BeginPlay()
{
	Super::BeginPlay();

	StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 2.0f, 0.0f));
	//StatusFlipbookComp->SetRelativeScale3D(FVector(2.0f, 0.0f, 2.5f));
	MirroredFlipbookComp->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
	//MirroredFlipbookComp->SetRelativeScale3D(FVector(2.0f, 0.0f, 2.5f));
}
