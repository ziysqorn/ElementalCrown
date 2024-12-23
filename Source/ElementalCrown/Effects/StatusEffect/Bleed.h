#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.h"
#include "Bleed.generated.h"

UCLASS()
class ELEMENTALCROWN_API ABleed : public ABaseStatus
{
	GENERATED_BODY()
protected:
	FTimerHandle DestroyHandle;
public:
	ABleed();
	void BeginPlay() override;
	void SelfDestroy();
	void BloodSpray() {
		StatusFlipbookComp->PlayFromStart();
	}
};