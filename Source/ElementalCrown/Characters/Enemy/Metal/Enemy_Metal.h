#pragma once

#include "CoreMinimal.h"
#include "../BaseEnemyCharacter.h"
#include "Enemy_Metal.generated.h"

/**
 *
 */
UCLASS()
class ELEMENTALCROWN_API AEnemy_Metal : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	//************************************* CONSTRUCTOR *****************************************
	AEnemy_Metal();

	virtual void BeginPlay() override;
};
