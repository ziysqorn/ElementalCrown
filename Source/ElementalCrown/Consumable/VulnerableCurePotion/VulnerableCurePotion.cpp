// Fill out your copyright notice in the Description page of Project Settings.


#include "VulnerableCurePotion.h"
#include "../../Characters/Main Character/MainCharacter.h"
#include "../../Effects/ConsumeAura/StatusCureAura/StatusCureAura.h"

UVulnerableCurePotion::UVulnerableCurePotion() : UConsumable(TEXT("/Script/Paper2D.PaperSprite'/Game/Assets/UI/ConsumableSlot/VulnerableCurePotion_Sprite.VulnerableCurePotion_Sprite'"))
{
	ConsumableName = "Vulnerable Cure Potion";
	ConsumablePrice = 12;
}

bool UVulnerableCurePotion::Consume()
{
	if (UConsumableComponent* ConsumableComponent = Cast<UConsumableComponent>(this->GetOuter())) {
		if (AMainCharacter* MainCharacter = ConsumableComponent->GetOwner<AMainCharacter>()) {
			if (MainCharacter && Quantity > 0) {
				if (UStatusEffectComponent* StatusEffectComponent = Cast<UStatusEffectComponent>(MainCharacter->GetStatusEffectComp())) {
					BaseStatusEffect* FoundStatus = StatusEffectComponent->FindStatusEffect(FName("Vulnerable"));
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
