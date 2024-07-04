// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../Effects/Skills/MagicArrow/FireArrow.h"
#include "ShootAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UShootAnimNotify : public UPaperZDAnimNotify
{
	GENERATED_BODY()
public:
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
};
