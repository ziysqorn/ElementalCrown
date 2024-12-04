// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaPotion.h"
#include "../../Effects/ConsumeAura/ManaAura/ManaAura.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "../ConsumableComponent.h"

UManaPotion::UManaPotion() : UConsumable(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/UI/ConsumableSlot/ManaPotion_Sprite.ManaPotion_Sprite'"))
{
	ConsumableName = "Cerulean Tears";
	ConsumablePrice = 6;
}

bool UManaPotion::Consume()
{
	if (UConsumableComponent* ConsumableComponent = Cast<UConsumableComponent>(this->GetOuter())) {
		if (ABaseCharacter* OwningCharacter = ConsumableComponent->GetOwner<ABaseCharacter>()) {
			if (OwningCharacter && Quantity > 0 && OwningCharacter->GetCurrentMana() < OwningCharacter->GetMaxMana()) {
				OwningCharacter->SetCurrentManaByBuff(ManaAmount);
				--Quantity;
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = OwningCharacter;
				if (AManaAura* ManaAura = OwningCharacter->GetWorld()->SpawnActor<AManaAura>(AManaAura::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
					ManaAura->AttachToActor(OwningCharacter, FAttachmentTransformRules::KeepRelativeTransform);
				}
				return true;
			}
		}
	}
	return false;
}
