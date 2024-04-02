// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableSkillAnimNotify.h"
#include "C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\Marketplace\PaperZD\Source\PaperZD\Public\AnimSequences\Players\PaperZDAnimPlayer.h"

void USpawnableSkillAnimNotify::SetSpawnProperty(UPaperZDAnimInstance* OwningInstance)
{
	if (OwningInstance->GetOwningActor()) {
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
			float CurrentPlaybackTime = OwningInstance->GetPlayer()->GetCurrentPlaybackTime();
			float CurrentAnimSequenceDuration = OwningInstance->GetPlayer()->GetCurrentAnimSequence()->GetTotalDuration();
			BaseCharacter->GetWorldTimerManager().SetTimer(FinishSkill, FTimerDelegate::CreateLambda([BaseCharacter]() {
				BaseCharacter->SetCharacterState(CharacterState::NONE);
				}), CurrentAnimSequenceDuration - CurrentPlaybackTime, false);
			SpawnLocation = BaseCharacter->GetSprite()->GetSocketLocation(FName("Eject Point"));
			SpawnRotation.Yaw = (BaseCharacter->GetSprite()->GetForwardVector().X > 0) ? 0 : 180;
		}
	}
}
