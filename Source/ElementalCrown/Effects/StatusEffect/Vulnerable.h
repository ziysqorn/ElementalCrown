#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.h"
#include "Vulnerable.generated.h"

UCLASS()
class ELEMENTALCROWN_API AVulnerable : public ABaseStatus
{
	GENERATED_BODY()
protected:
	USceneComponent* SymmetryPoint = nullptr;
	UPaperFlipbookComponent* MirroredFlipbookComp = nullptr;
public:
	AVulnerable();
	void BeginPlay() override;
};