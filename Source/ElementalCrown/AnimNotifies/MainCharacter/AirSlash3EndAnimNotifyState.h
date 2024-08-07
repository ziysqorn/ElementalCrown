// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "../../Effects/Impact/AttackImpact/BloodSlashImpact.h"
#include "../../Effects/Impact/AttackImpact/NoBloodSlashImpact.h"
#include "AirSlash3EndAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UAirSlash3EndAnimNotifyState : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()
protected:
	//Attribute
	int Buff{0};
	UPROPERTY(EditDefaultsOnly, Category = "Box Extent")
	FVector BoxExtent;
public:
	UAirSlash3EndAnimNotifyState();
	virtual void SetBuff(const int& inBuff) {
		this->Buff = inBuff;
	}
	virtual void SpawnImpact(APaperZDCharacter* Character, const ECollisionChannel& OwnerObjectType, const FHitResult& Target) const;
	//Events
	void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
