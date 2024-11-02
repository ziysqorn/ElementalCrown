#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.generated.h"

UCLASS()
class ELEMENTALCROWN_API ABaseStatus : public AActor
{
	GENERATED_BODY()
protected:
	UPaperFlipbookComponent* StatusFlipbookComp = nullptr;
public:
	ABaseStatus();
	ABaseStatus(const TCHAR* FlipbookRef, bool isCustom);
};