#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.h"
#include "Bleed.generated.h"

UCLASS()
class ELEMENTALCROWN_API ABleed : public ABaseStatus
{
	GENERATED_BODY()

public:
	ABleed();
	void BloodSpray() {
		StatusFlipbookComp->PlayFromStart();
	}
};