#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.h"
#include "Vulnerable.generated.h"

UCLASS()
class ELEMENTALCROWN_API AVulnerable : public ABaseStatus
{
	GENERATED_BODY()

public:
	AVulnerable();
	void BeginPlay() override;
};