// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "../UI/DialogueUI/DialogueUI.h"
#include "../Characters/Main Character/MainCharacter.h"
#include "DialogueTriggerActor.generated.h"

UCLASS()
class ELEMENTALCROWN_API ADialogueTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueTriggerActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Root Scene Comp")
	USceneComponent* RootScene = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Trigger Box")
	UBoxComponent* TriggerBox = nullptr;

	UPROPERTY(EditAnywhere, Category = "Dialogue array")
	TArray<FDialogueLine> DialogueLines;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Dialogue UI Subclass")
	TSubclassOf<UDialogueUI> DialogueUISubclass;

	bool isTrigger = false;

	FTimerHandle DisplayDialogueHandle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void ActionAfterDialogue();

public:

	FDialogueLine* GetDialogueLineAt(int idx) {
		if (DialogueLines.IsValidIndex(idx)) {
			return &DialogueLines[idx];
		}
		return nullptr;
	}

};