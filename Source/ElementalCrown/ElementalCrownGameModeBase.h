// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ElementalCrownGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API AElementalCrownGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AElementalCrownGameModeBase();
	void BeginPlay() override;
};
