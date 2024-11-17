// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaPotion.h"
#include "../../Effects/ConsumeAura/ManaAura/ManaAura.h"

ManaPotion::ManaPotion() : Consumable(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/UI/ConsumableSlot/ManaPotion_Sprite.ManaPotion_Sprite'"))
{
}

ManaPotion::~ManaPotion()
{
}

void ManaPotion::Consume()
{
	if (OwningCharacter && Quantity > 0 && OwningCharacter->GetCurrentMana() < OwningCharacter->GetMaxMana()) {
		OwningCharacter->SetCurrentManaByBuff(ManaAmount);
		--Quantity;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningCharacter;
		if (AManaAura* ManaAura = OwningCharacter->GetWorld()->SpawnActor<AManaAura>(AManaAura::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
			ManaAura->AttachToActor(OwningCharacter, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}
