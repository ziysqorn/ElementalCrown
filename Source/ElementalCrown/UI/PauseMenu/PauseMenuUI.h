// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "PauseMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class ELEMENTALCROWN_API UPauseMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeOnInitialized() override;
	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* Btn_Resume = nullptr;
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* Btn_ReturnToMenu = nullptr;
public:
	UFUNCTION()
	void ResumeClick();

	UFUNCTION()
	void ReturnToMenuClick();


	void CloseMenu();
};
