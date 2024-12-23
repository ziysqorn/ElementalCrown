// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueUI.h"
#include "../../GameplayActors/DialogueTriggerActor.h"

void UDialogueUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetIsFocusable(true);
}

void UDialogueUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (DialogueLines) {
		if (FDialogueLine* DialogueLine = &(*DialogueLines)[CurrentDialogueLine]) {
			Txt_SpeakerName->SetText(FText::FromName(DialogueLine->SpeakerName));
			Txt_Dialogue->SetText(DialogueLine->DialogueText);
		}
	}
}

FReply UDialogueUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().GetFName().IsEqual("E")) {
		if (DialogueLines) {
			++CurrentDialogueLine;
			if (CurrentDialogueLine >= DialogueLines->Num()) {
				DialogueEndDel.ExecuteIfBound();
				if (APlayerController* PlayerController = this->GetOwningPlayer()) {
					if (PlayerController->GetPawn()) PlayerController->GetPawn()->EnableInput(PlayerController);
					this->RemoveFromParent();
				}
			}
			else if (FDialogueLine* DialogueLine = &(*DialogueLines)[CurrentDialogueLine]) {
				Txt_SpeakerName->SetText(FText::FromName(DialogueLine->SpeakerName));
				Txt_Dialogue->SetText(DialogueLine->DialogueText);
			}
		}
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UDialogueUI::SetDialogueLines(TArray<FDialogueLine>* Dialogue)
{
	DialogueLines = Dialogue;
}
