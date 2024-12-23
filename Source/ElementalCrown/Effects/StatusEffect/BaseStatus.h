#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.generated.h"

UCLASS()
class ELEMENTALCROWN_API ABaseStatus : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Symmetry Flipbook Point")
	UPaperFlipbookComponent* MirroredFlipbookComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Status Flipbook Point")
	UPaperFlipbookComponent* StatusFlipbookComp = nullptr;
public:
	ABaseStatus();
	ABaseStatus(const TCHAR* Ref);
	virtual void BeginPlay() override;
};