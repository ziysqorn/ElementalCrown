// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnStatus.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

BurnStatus::BurnStatus() : BaseStatusEffect(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/Effect/StatusEffect/Burn/Sprite/burning_loop_1_Sprite_6.burning_loop_1_Sprite_6'"), TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Effect/StatusEffect/Burn/Flipbook/StatusEffect_Burn_Main.StatusEffect_Burn_Main'"))
{
	StatusName = "Burn";
	AffectingTime = 4.0f;
}

BurnStatus::~BurnStatus()
{
	if (AffectedCharacter) {
		if(AffectedCharacter->GetWorldTimerManager().IsTimerActive(EffectHandle)) AffectedCharacter->GetWorldTimerManager().ClearTimer(EffectHandle);
		if(AffectedCharacter->GetWorldTimerManager().IsTimerActive(EffectEndHandle)) AffectedCharacter->GetWorldTimerManager().ClearTimer(EffectEndHandle);
	}
}

void BurnStatus::ExecuteStatus()
{
	if (OwningCharacter && AffectedCharacter) {
		StatusFlipbookComp = NewObject<UPaperFlipbookComponent>(AffectedCharacter, UPaperFlipbookComponent::StaticClass());
		StatusFlipbookComp->RegisterComponent();
		StatusFlipbookComp->AttachToComponent(AffectedCharacter->GetSprite(), FAttachmentTransformRules::KeepRelativeTransform);
		StatusFlipbookComp->SetRelativeLocation(FVector(0.0f, 5.0f, 0.0f));
		StatusFlipbookComp->SetRelativeScale3D(FVector(1.5f, 0.0f, 1.5f));
		StatusFlipbookComp->SetFlipbook(StatusFlipbook);
		StatusFlipbookComp->PlayFromStart();
		AffectedCharacter->GetWorldTimerManager().SetTimer(EffectEndHandle, FTimerDelegate::CreateLambda([this]() {
			if (OwningCharacter && AffectedCharacter) {
				StatusFlipbookComp->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
				auto CurStatusList = AffectedCharacter->GetStatusList();
				for (int i = 0; i < CurStatusList->Num(); ++i) {
					TSharedPtr<BaseStatusEffect> cur = (*CurStatusList)[i];
					if (cur->GetStatusName() == "Burn") CurStatusList->RemoveAt(i);
				}
			}
		}), AffectingTime, false);
		AffectedCharacter->GetWorldTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([this]() {
			if (OwningCharacter && AffectedCharacter) {
				TSubclassOf<UDamageType> DamageType;
				UGameplayStatics::ApplyDamage(AffectedCharacter, BurnDamage, OwningCharacter->GetController(), OwningCharacter, DamageType);
			}
		}), TimeBetweenEachBurn, true);
	}
}


