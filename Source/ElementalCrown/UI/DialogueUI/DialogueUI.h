// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../CustomStructures/DialogueLine.h"
#include "DialogueUI.generated.h"

/**
 * 
 */

class ADialogueTriggerActor;

DECLARE_DELEGATE(FDialogueEnd)

UCLASS()
class ELEMENTALCROWN_API UDialogueUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeOnInitialized() override;
	void NativeConstruct() override;
	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	TArray<FDialogueLine>* DialogueLines;


	int CurrentDialogueLine = 0;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* Txt_SpeakerName = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* Txt_Dialogue = nullptr;

public:
	FDialogueEnd DialogueEndDel;

	void SetDialogueLines(TArray<FDialogueLine>* Dialogue);
};
