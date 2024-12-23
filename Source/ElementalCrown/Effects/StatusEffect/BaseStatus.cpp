#include "BaseStatus.h"

ABaseStatus::ABaseStatus()
{

}

ABaseStatus::ABaseStatus(const TCHAR* Ref)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Symmetric Point");

	StatusFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Status Flipbook Component");
	MirroredFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Mirrored Flipbook Component");

	MirroredFlipbookComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StatusFlipbookComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRef(Ref);
	UPaperFlipbook* Flipbook = FlipbookRef.Object;
	if (Flipbook) StatusFlipbookComp->SetFlipbook(Flipbook);
	MirroredFlipbookComp->SetFlipbook(StatusFlipbookComp->GetFlipbook());


	if (MirroredFlipbookComp) MirroredFlipbookComp->SetLooping(false);
	if (StatusFlipbookComp) StatusFlipbookComp->SetLooping(false);
}

void ABaseStatus::BeginPlay()
{
	Super::BeginPlay();
	
	StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 2.0f, 0.0f));
	MirroredFlipbookComp->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
	StatusFlipbookComp->SetRelativeScale3D(FVector(2.0f, 1.0f, 2.5f));
	MirroredFlipbookComp->SetRelativeScale3D(FVector(2.0f, 1.0f, 2.5f));
}
