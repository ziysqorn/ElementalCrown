// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ElementalWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
UCLASS()
class ELEMENTALCROWN_API UElementalWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "ElementalWidget", meta = (BindWidget))
	UImage* ElementalFrame = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "ElementalWidget", meta = (BindWidget))
	UImage* ElementalIcon = nullptr;
};
