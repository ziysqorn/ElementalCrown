#include "Bleed.h"

ABleed::ABleed() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Bleed/Flipbook/StatusEffect_Bleed.StatusEffect_Bleed'"))
{
}

void ABleed::BeginPlay()
{
	Super::BeginPlay();

	StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 2.0f, 0.0f));
	StatusFlipbookComp->SetRelativeScale3D(FVector(2.0f, 1.0f, 3.0f));
	MirroredFlipbookComp->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
	MirroredFlipbookComp->SetRelativeScale3D(FVector(2.0f, 1.0f, 3.0f));

	this->GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateUObject(this, &ABleed::SelfDestroy), StatusFlipbookComp->GetFlipbook()->GetTotalDuration(), false);
}

void ABleed::SelfDestroy()
{
	this->Destroy();
}
