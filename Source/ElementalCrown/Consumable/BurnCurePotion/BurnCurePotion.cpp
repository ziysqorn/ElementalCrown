// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnCurePotion.h"
#include "../../Characters/Main Character/MainCharacter.h"
#include "../../Effects/ConsumeAura/StatusCureAura/StatusCureAura.h"

UBurnCurePotion::UBurnCurePotion() : UConsumable(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/UI/ConsumableSlot/BurnCurePotion_Sprite.BurnCurePotion_Sprite'"))
{
	ConsumableName = "Burn Cure Potion";
	ConsumablePrice = 8;
}

bool UBurnCurePotion::Consume()
{
	if (UConsumableComponent* ConsumableComponent = Cast<UConsumableComponent>(this->GetOuter())) {
		if (AMainCharacter* MainCharacter = ConsumableComponent->GetOwner<AMainCharacter>()) {
			if (MainCharacter && Quantity > 0) {
				if (UStatusEffectComponent* StatusEffectComponent = Cast<UStatusEffectComponent>(MainCharacter->GetStatusEffectComp())) {
					UBaseStatusEffect* FoundStatus = StatusEffectComponent->FindStatusEffect(FName("Burn"));
					if (FoundStatus) {
						--Quantity;
						StatusEffectComponent->RemoveStatusEffect(FoundStatus);
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = MainCharacter;
						if (AStatusCureAura* StatusCureAura = MainCharacter->GetWorld()->SpawnActor<AStatusCureAura>(AStatusCureAura::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
							StatusCureAura->AttachToActor(MainCharacter, FAttachmentTransformRules::KeepRelativeTransform);
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}
