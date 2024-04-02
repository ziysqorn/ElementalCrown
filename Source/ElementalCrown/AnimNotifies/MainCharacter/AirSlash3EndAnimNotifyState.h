// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotifyState.h"
#include "../../Interface/BaseCharacterInterface.h"
#include "../../Characters/Main Character/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
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
	virtual void SetBuff();
	virtual void SpawnImpact(APaperZDCharacter* Character, const ECollisionChannel& OwnerObjectType, const FHitResult& Target);
	//Events
	void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) override;
	void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) override;
};
