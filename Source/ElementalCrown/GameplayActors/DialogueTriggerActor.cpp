// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTriggerActor.h"
#include "../Controller/MainController.h"
#include "../Characters/BossCharacter/BossCharacter.h"

// Sets default values
ADialogueTriggerActor::ADialogueTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	RootScene->SetupAttachment(RootComponent);
	TriggerBox->AttachToComponent(RootScene, FAttachmentTransformRules::KeepRelativeTransform);

	OnActorBeginOverlap.AddDynamic(this, &ADialogueTriggerActor::BeginOverlap);
}

// Called when the game starts or when spawned
void ADialogueTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
}

void ADialogueTriggerActor::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!isTrigger) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor)) {
			if (AMainController* MainController = MainCharacter->GetController<AMainController>()) {
				MainCharacter->DisableInput(MainController);
				GetWorldTimerManager().SetTimer(DisplayDialogueHandle, FTimerDelegate::CreateLambda([this, MainController]() {
					if (DialogueUISubclass) {
						if (UDialogueUI* DialogueUI = CreateWidget<UDialogueUI>(MainController, DialogueUISubclass)) {
							DialogueUI->DialogueEndDel.BindUObject(this, &ADialogueTriggerActor::ActionAfterDialogue);
							DialogueUI->SetOwningPlayer(MainController);
							DialogueUI->SetDialogueLines(&DialogueLines);
							DialogueUI->AddToViewport(11);
							DialogueUI->SetFocus();
							isTrigger = true;
						}
					}
				}), 1.5f, false);
			}
		}
	}
}

void ADialogueTriggerActor::ActionAfterDialogue()
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors, ABossCharacter::StaticClass());
	for (int i = 0; i < actors.Num(); ++i) {
		if (ABossCharacter* BossCharacter = Cast<ABossCharacter>(actors[i])) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("START BATTLE"));
			BossCharacter->MakeDecision();
			if (AMainController* MainController = Cast<AMainController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
				if (UBossHealthBar* BossHealthBar = MainController->GetBossHealthBar()) {
					BossHealthBar->SetBossName(FText::FromName(BossCharacter->GetCharacterName()));
					BossHealthBar->SetDelegateForHealthBar(BossCharacter, FName("GetHealthPercentage"));
					MainController->BossHealthBarDisplay();
				}
			}
			break;
		}
	}
}

