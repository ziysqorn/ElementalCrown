#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.h"
#include "Burn.generated.h"

UCLASS()
class ELEMENTALCROWN_API ABurn : public ABaseStatus
{
	GENERATED_BODY()
protected:
	USceneComponent* SymmetryPoint = nullptr;
	UPaperFlipbookComponent* MirroredFlipbookComp = nullptr; 
public:
	ABurn();
	void BeginPlay() override;
};