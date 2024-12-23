#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BaseStatus.h"
#include "Burn.generated.h"

UCLASS()
class ELEMENTALCROWN_API ABurn : public ABaseStatus
{
	GENERATED_BODY()
public:
	ABurn();
	void BeginPlay() override;
};