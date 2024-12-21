// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "BossHealthBar.generated.h"

/**
 * 
 */

UCLASS()
class ELEMENTALCROWN_API UBossHealthBar : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Boss Name", meta = (BindWidget))
	UTextBlock* BossName = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Boss Health Bar", meta = (BindWidget))
	UProgressBar* HealthBar = nullptr;
public:
	void SetHealthBarPercent(const float& inPercent) {
		if (HealthBar) HealthBar->SetPercent(inPercent);
	}
	void SetBossName(FText name) {
		if(BossName) BossName->SetText(name);
	}
	void SetDelegateForHealthBar(UObject* object, const FName& funcName) {
		if (HealthBar) HealthBar->PercentDelegate.BindUFunction(object, funcName);
	}
	UProgressBar* GetHealthBar() {
		return HealthBar;
	}
};
