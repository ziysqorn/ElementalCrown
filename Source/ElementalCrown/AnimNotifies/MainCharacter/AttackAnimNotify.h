// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "../../Effects/Impact/AttackImpact/BloodSlashImpact.h"
#include "../../Effects/Impact/AttackImpact/NoBloodSlashImpact.h"
#include "AttackAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UAttackAnimNotify : public UPaperZDAnimNotify
{
	GENERATED_BODY()

protected:
	//Attribute
	int Buff{0};
	UPROPERTY(EditDefaultsOnly, Category = "Box Position")
	FVector BoxPosition= FVector(40, 0, 5);

	UPROPERTY(EditDefaultsOnly, Category = "Box Extent")
	FVector BoxExtent= FVector(30, 0, 40);

public:
	UAttackAnimNotify();
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void SetBuff(const int& inBuff) {
		this->Buff = inBuff;
	}
	virtual void SpawnImpact(APaperZDCharacter* Character, const ECollisionChannel& OwnerObjectType, const FHitResult& Target) const;
};