#include "BaseStatus.h"

ABaseStatus::ABaseStatus()
{
	StatusFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Status Flipbook Component");
	StatusFlipbookComp->SetupAttachment(RootComponent);
}

ABaseStatus::ABaseStatus(const TCHAR* FlipbookRef, bool isCustom)
{
	if (!isCustom) {
		StatusFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Status Flipbook Component");
		StatusFlipbookComp->SetupAttachment(RootComponent);
		UPaperFlipbook* Flipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, FlipbookRef));
		if (Flipbook) StatusFlipbookComp->SetFlipbook(Flipbook);
	}
	else {
		StatusFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Status Flipbook Component");
		UPaperFlipbook* Flipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, FlipbookRef));
		if (Flipbook) StatusFlipbookComp->SetFlipbook(Flipbook);
	}
}
