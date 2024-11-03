#include "Bleed.h"

ABleed::ABleed() : ABaseStatus(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Bleed/Flipbook/StatusEffect_Bleed.StatusEffect_Bleed'"), true)
{
	SymmetryPoint = CreateDefaultSubobject<USceneComponent>("Symmetric Point");
	SymmetryPoint->SetupAttachment(RootComponent);
	MirroredFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Mirrored Flipbook Component");
	MirroredFlipbookComp->AttachToComponent(SymmetryPoint, FAttachmentTransformRules::KeepRelativeTransform);
	StatusFlipbookComp->AttachToComponent(SymmetryPoint, FAttachmentTransformRules::KeepRelativeTransform);
	MirroredFlipbookComp->SetFlipbook(StatusFlipbookComp->GetFlipbook());
	if (MirroredFlipbookComp) MirroredFlipbookComp->SetLooping(false);
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(false);
}

void ABleed::BeginPlay()
{
	Super::BeginPlay();

	StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 2.0f, 0.0f));
	StatusFlipbookComp->SetRelativeScale3D(FVector(2.0f, 0.0f, 3.0f));
	MirroredFlipbookComp->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
	MirroredFlipbookComp->SetRelativeScale3D(FVector(2.0f, 0.0f, 3.0f));

	this->GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([this]() {
		this->Destroy();
		}), StatusFlipbookComp->GetFlipbook()->GetTotalDuration(), false);
}
