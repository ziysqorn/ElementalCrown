// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Enemy Health Bar", meta = (BindWidget))
	UProgressBar* HealthBar = nullptr;

public:
	void SetHealthBarPercent(const float& inPercent) {
		HealthBar->SetPercent(inPercent);
	}
	void SetDelegateForHealthBar(UObject* object, const FName& funcName) {
		HealthBar->PercentDelegate.BindUFunction(object, funcName);
	}
	UProgressBar* GetHealthBar() {
		return HealthBar;
	}
};
