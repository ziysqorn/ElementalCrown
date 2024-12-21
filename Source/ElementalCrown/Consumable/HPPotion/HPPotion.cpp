// Fill out your copyright notice in the Description page of Project Settings.


#include "HPPotion.h"
#include "../../Effects/ConsumeAura/HealAura/HealAura.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "../ConsumableComponent.h"

UHPPotion::UHPPotion() : UConsumable(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/UI/ConsumableSlot/HPPotion_Sprite.HPPotion_Sprite'"))
{
	ConsumableName = "Crimson Tears";
	ConsumablePrice = 6;
	Quantity = maxQuantity;
}


bool UHPPotion::Consume()
{
	if (UConsumableComponent* ConsumableComponent = Cast<UConsumableComponent>(this->GetOuter())) {
		if (ABaseCharacter* OwningCharacter = ConsumableComponent->GetOwner<ABaseCharacter>()) {
			if (OwningCharacter && Quantity > 0 && OwningCharacter->GetCurrentHealth() < OwningCharacter->GetMaxHealth()) {
				OwningCharacter->SetCurrentHealthByBuff(HealAmount);
				--Quantity;
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = OwningCharacter;
				if (AHealAura* HealAura = OwningCharacter->GetWorld()->SpawnActor<AHealAura>(AHealAura::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
					HealAura->AttachToActor(OwningCharacter, FAttachmentTransformRules::KeepRelativeTransform);
				}
				return true;
			}
		}
	}
	return false;
}
