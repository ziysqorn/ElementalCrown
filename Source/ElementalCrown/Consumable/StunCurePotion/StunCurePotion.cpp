// Fill out your copyright notice in the Description page of Project Settings.


#include "StunCurePotion.h"
#include "../../Characters/Main Character/MainCharacter.h"
#include "../../Effects/ConsumeAura/StatusCureAura/StatusCureAura.h"

UStunCurePotion::UStunCurePotion() : UConsumable(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/UI/ConsumableSlot/StunCurePotion_Sprite.StunCurePotion_Sprite'"))
{
	ConsumableName = "Stun Cure Potion";
	ConsumablePrice = 10;
}

bool UStunCurePotion::Consume()
{
	if (UConsumableComponent* ConsumableComponent = Cast<UConsumableComponent>(this->GetOuter())) {
		if (AMainCharacter* MainCharacter = ConsumableComponent->GetOwner<AMainCharacter>()) {
			if (MainCharacter && Quantity > 0) {
				if (UStatusEffectComponent* StatusEffectComponent = Cast<UStatusEffectComponent>(MainCharacter->GetStatusEffectComp())) {
					BaseStatusEffect* FoundStatus = StatusEffectComponent->FindStatusEffect(FName("Stun"));
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
