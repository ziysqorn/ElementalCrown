// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatusEffect.h"
#include "../UI/StatusEffectProgressUI/StatusEffectProgressUI.h"
#include "StatusEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTALCROWN_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TArray<UBaseStatusEffect*> StatusList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StatusProgressSubClass")
	TSubclassOf<UStatusEffectProgressUI> BurnProgressSubClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StatusProgressSubClass")
	TSubclassOf<UStatusEffectProgressUI> VulnerableProgSubClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StatusProgressSubClass")
	TSubclassOf<UStatusEffectProgressUI> StunProgressSubClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StatusProgressSubClass")
	TSubclassOf<UStatusEffectProgressUI> BleedProgressSubClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StatusProgressSubClass")
	TSubclassOf<UStatusEffectProgressUI> DrowsyProgressSubClass;

public:	
	UStatusEffectComponent();

	void AddStatusEffect(UBaseStatusEffect* Effect);

	void RemoveStatusEffect(UBaseStatusEffect* Effect);

	void ClearAllStatusEffect();

	int FindStatusEffect(UBaseStatusEffect* Effect) {
		return StatusList.Find(Effect);
	}

	UBaseStatusEffect* FindStatusEffect(const FName& inName) {
		UBaseStatusEffect** res = nullptr;
		res = StatusList.FindByPredicate([inName](const UBaseStatusEffect* StatusEffect) {
			return StatusEffect->GetStatusName().IsEqual(inName);
			});
		return res ? *res : nullptr;
	}
	
	TArray<UBaseStatusEffect*>* GetStatusList() {
		return &StatusList;
	}

	UStatusEffectProgressUI* GetProgressUI(UBaseStatusEffect* Effect);
protected:
	virtual void BeginPlay() override;
		
};
