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

	TArray<BaseStatusEffect*> StatusList;

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

	void AddStatusEffect(BaseStatusEffect* Effect);

	void RemoveStatusEffect(BaseStatusEffect* Effect);

	void ReduceStatusBuildup(BaseStatusEffect* Effect);

	void ClearAllStatusEffect();

	int FindStatusEffect(BaseStatusEffect* Effect) {
		return StatusList.Find(Effect);
	}

	BaseStatusEffect* FindStatusEffect(const FName& inName) {
		BaseStatusEffect** res = nullptr;
		res = StatusList.FindByPredicate([inName](const BaseStatusEffect* StatusEffect) {
			return StatusEffect->GetStatusName().IsEqual(inName);
			});
		return res ? *res : nullptr;
	}
	
	TArray<BaseStatusEffect*>* GetStatusList() {
		return &StatusList;
	}

	UStatusEffectProgressUI* GetProgressUI(BaseStatusEffect* Effect);
protected:
	virtual void BeginPlay() override;
		
};
